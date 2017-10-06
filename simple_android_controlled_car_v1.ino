/***************************************************************************
 Example Code of an Android Phone(Tab) controlled  mobile robot 
 using the Saleng Mobile Robot Shield, a bluetooth module and a 2-wheel (or 4-wheel) robot chassis.
 
 This software is free provided that this notice is not removed and proper attribution 
 is accorded to Layad Circuits and its Author(s).
 Layad Circuits invests resources in producing free software. By purchasing Layad Circuits'
 products or utilizing its services, you support the continuing development of free software
 for all.

 The Saleng Mobile Robot Shield is designed and made by Layad Circuits.
 By supporting our products, you support local innovation and share in the movement
 to spur local ingenuity. 
  
 Author(s): C.D.Malecdan for Layad Circuits Electronics Engineering
 Revision: 1.0 - 2017/09/27 - initial release
 Layad Circuits Electronics Engineering Supplies and Services
 B314 Lopez Bldg., Session Rd. cor. Assumption Rd., Baguio City, Philippines
 www.layadcircuits.com
 general: info@layadcircuits.com
 sales: sales@layadcircuits.com
 +63-916-442-8565
 ***************************************************************************/
#include <SoftwareSerial.h>
SoftwareSerial bt(12, A3); //these pins are from the T1 and E1 pins of the Shield.
                           //Connect the bluetooth module Tx and Rx pins to the Shield's T1 and E1 respectively.
                           //Connect the bluetooth Vcc to any + pin and ground to any - pin of the shield

// bluetooth related
const char BT_FORWARD = 'f';
const char BT_LEFT = 'l';
const char BT_RIGHT = 'r';
const char BT_BACKWARD = 'b';
const char BT_STOP = 's';
// NOTE: speed control characters: '0'(slowest) to '9' (fastest)
// The bluetooth PIN is by default, 1234

#define AIN1 2 
#define BIN1 7
#define AIN2 4
#define BIN2 5
#define PWMA 3
#define PWMB 6
#define STBY 8

void speedSetting(byte val)
{
  analogWrite(PWMA,val);
  analogWrite(PWMB,val);
}

void forward()
{
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,HIGH);
  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,HIGH);
}

void backward()
{
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2,LOW);
}

void turnleft()
{
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,HIGH);
  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2,LOW);
}

void turnright()
{
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,HIGH);
}

void motorstop()
{
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,LOW);
}

void shortbreak()
{
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,HIGH);
  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2,HIGH);
}



void bluetooth()
{
  static unsigned long t;
  static unsigned long rxtimer;
  
  if(bt.available())
  {
    char c=bt.read();
    Serial.print(c);
    rxtimer = millis();
    switch(c)
    {
      case BT_STOP:
        motorstop();
      break;
      
      case BT_FORWARD:    
        forward();
      break;
        
      case BT_LEFT:
        turnleft();
      break;
       
      case BT_RIGHT:
        turnright();
      break;
       
      case BT_BACKWARD:
        backward();
      break;    

      case '0': speedSetting(25); break;
      case '1': speedSetting(50); break;
      case '2': speedSetting(75); break;
      case '3': speedSetting(100); break;
      case '4': speedSetting(125); break;
      case '5': speedSetting(150); break;
      case '6': speedSetting(175); break;
      case '7': speedSetting(200); break;
      case '8': speedSetting(225); break;
      case '9': speedSetting(255); break;
    }
  }

  if(millis() - rxtimer >= 1000) motorstop();
}

void setup() {
  Serial.begin(9600);
  bt.begin(9600);
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(BIN1,OUTPUT);
  pinMode(BIN2,OUTPUT);
  pinMode(STBY,OUTPUT);
  digitalWrite(STBY,HIGH);//enable driver
  speedSetting(100); //default
  //Serial.begin(115200);
  Serial.println("start");
  bt.println("start");
  
}

void loop() {
  bluetooth();
} 
