#include<LiquidCrystal.h>
#include <SoftwareSerial.h>

#define echo 9
#define trigger 10
#define tank_pump 4
#define watering_pump 13
#define moisture_sensor A0
long duration;
int distance;
int moisture_value;
int distance_percent;
int moist_percent;
int value = 0;
int lm35 = A1;
SoftwareSerial SIM900(0,1);
LiquidCrystal lcd(12,11,8,7,6,5);

void setup () {
lcd.begin(20,4);
SIM900.begin(9600);
Serial.begin(9600);
pinMode(echo,INPUT);
pinMode(moisture_sensor,INPUT);
pinMode(trigger,OUTPUT);
pinMode(3,INPUT);
digitalWrite(trigger,LOW);
pinMode(watering_pump,OUTPUT);
pinMode(tank_pump,OUTPUT);
digitalWrite(watering_pump,LOW);
digitalWrite(tank_pump,LOW);
lcd.setCursor(0,1);
lcd.print("SMART IRRIGATION" );
lcd.setCursor(0,2);
lcd.print(" MBSD LAB ");
lcd.setCursor(0,3);
lcd.print("  WELCOME  ");
delay(500);
lcd.clear(); 
}


void loop(){

 // LEVEL SENSOR
 digitalWrite(trigger,LOW);
 delayMicroseconds(2);
 digitalWrite(trigger,HIGH);
 delayMicroseconds(10); 
 digitalWrite(trigger,LOW);
 duration=pulseIn(echo,HIGH);
 distance=duration*0.017; 
 distance_percent=map( distance,0,1023,0,100);
 moisture_value= analogRead(moisture_sensor);
moist_percent=map(moisture_value,0,1023,0,100);
 condition();

 //TEMPERATURE SENSOR
 value = analogRead(lm35);
  float milivolts = (value/1024.0)*5*1000;
  float cel = milivolts/10;
  Serial.print("Temperature=");
  Serial.print(cel);
  Serial.print("*c");
  Serial.println();
  if(cel>35)
  {
    Serial.println("Temperature has hit MAX levels, Activating Pumps");
    digitalWrite(watering_pump,HIGH);
  }
  delay(1000);

  //RAIN SENSOR
   int rain = digitalRead(3);

   if(rain==1 && moist_percent>85)
   {
  Serial.println("Its Raining");
  digitalWrite(watering_pump,LOW);
   delay(500);
   }
   else if(rain==0)
  {
  Serial.println("No Rain");
   delay(500);
  }

  
}


void sms(){
SIM900.println("WATERING PUMP IS OFF"); // message to send
SIM900.println((char)26); // End AT command with a ^Z, ASCII code 26
Serial.println((char)26);
SIM900.println();

}

void sms1(){

SIM900.println("TANK PUMP IS OFF"); // message to send
Serial.println("TANK PUMP IS OFF");

SIM900.println((char)26); // End AT command with a ^Z, ASCII code 26
Serial.println((char)26);
//delay(200);
SIM900.println();

}


void sms2(){

SIM900.println("WATERING PUMP IS ON"); // message to send
Serial.println("WATERING PUMP IS ON");
//delay(200);
SIM900.println((char)26); // End AT command with a ^Z, ASCII code 26
Serial.println((char)26);
//delay(200);
SIM900.println();

}

void sms3(){

SIM900.println("TANK PUMP IS ON"); // message to send
Serial.println("TANK PUMP IS ON");
//delay(200);
SIM900.println((char)26); // End AT command with a ^Z, ASCII code 26
Serial.println((char)26);
//delay(200);
SIM900.println();

}


void condition(){
if (distance_percent>65 &&moist_percent<85){
LCD_3();
digitalWrite(tank_pump,LOW);
digitalWrite(watering_pump,HIGH);
 sms1();
 sms2();
delay(1000);
}
else if (distance_percent<65 &&moist_percent>85)
{
LCD_2();
digitalWrite(tank_pump,HIGH);
digitalWrite(watering_pump,LOW);
sms3();
sms();
delay(1000);
}
else if (distance_percent>65 &&moist_percent>85)
{

LCD_4();
digitalWrite(tank_pump,LOW);
digitalWrite(watering_pump,LOW);

sms1();
sms();
delay(1000);

}

else if (distance_percent<65 &&moist_percent<85)
{
LCD_1();
digitalWrite(tank_pump,HIGH);
digitalWrite(watering_pump,HIGH);
sms3();
sms2();
delay(1000);

}

}



  void LCD_1()
  {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("TANK LEVEL=  ");
  lcd.print(distance_percent);
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("MOIST CONTENT= ");
  lcd.print(moist_percent);
  lcd.print("%");
   lcd.setCursor(0,2);
  lcd.print("W-PUMP STATUS  ");
  lcd.print("  ON");
  lcd.setCursor(0,3);
  lcd.print("T-PUMP STATUS  ");
  lcd.print("  ON");
  }

void LCD_2(){
  lcd.clear();
  lcd.setCursor(0,0);
   lcd.print("TANK LEVEL=  ");
  lcd.print(distance_percent);
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("MOIST CONTENT= ");
  lcd.print(moist_percent);
  lcd.print("%");
   lcd.setCursor(0,2);
  lcd.print("W-PUMP STATUS ");
  lcd.print("  OFF");
  lcd.setCursor(0,3);
  lcd.print("T-PUMP STATUS ");
  lcd.print("   ON");
  }
  void LCD_3(){
  lcd.clear();
  lcd.setCursor(0,0);
   lcd.print("TANK LEVEL=  ");
  lcd.print(distance_percent);
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("MOIST CONTENT= ");
  lcd.print(moist_percent);
  lcd.print("%");
   lcd.setCursor(0,2);
  lcd.print("W-PUMP STATUS ");
  lcd.print("  ON");
  lcd.setCursor(0,3);
  lcd.print("T-PUMP STATUS ");
  lcd.print("  OFF");
  }

  void LCD_4(){
  lcd.clear();
  lcd.setCursor(0,0);
   lcd.print("TANK LEVEL=  ");
  lcd.print(distance_percent);
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("MOIST CONTENT= ");
  lcd.print(moist_percent);
  lcd.print("%");
   lcd.setCursor(0,2);
  lcd.print("W-PUMP STATUS");
  lcd.print("  OFF");
  lcd.setCursor(0,3);
  lcd.print("T-PUMP STATUS");
  lcd.print("  OFF");
  }
