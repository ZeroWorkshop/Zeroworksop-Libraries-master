#include <Wire.h>
#include "StarterPro.h"
#include <ZeroMotors.h>
#include <Pushbutton.h>


#define _INCLUDE_BUZZER_ 

ZeroMotors motors;
Pushbutton START(ZERO_BUTTON);

void setup()
{                       
  playPowerOn();
  pinMode(ZW_A1,INPUT);
  pinMode(ZW_A2,INPUT);
  pinMode(ZW_A3,INPUT);
  pinMode(ZW_A4,INPUT);
  pinMode(ZW_B1,OUTPUT);
  pinMode(ZW_B2,OUTPUT);
  pinMode(ZW_B3,OUTPUT);
  pinMode(ZW_B4,OUTPUT);
  digitalWrite(ZW_B1,LOW);
  digitalWrite(ZW_B2,LOW);
  digitalWrite(ZW_B3,LOW);
  digitalWrite(ZW_B4,LOW);
  motors.motorControl(M1,0);
  motors.motorControl(M2,0);
  motors.motorControl(M3,0);
  motors.motorControl(M4,0);
  Serial.begin(115200);
  START.waitForButton();
  playStart();  

}

void loop()
{
  // run left motor forward
  int a1_val,a2_val,a3_val,a4_val;
  
  a1_val = digitalRead(ZW_A1);
  a2_val = digitalRead(ZW_A2);
  a3_val = digitalRead(ZW_A3);
  a4_val = digitalRead(ZW_A4);

  Serial.print(a1_val);Serial.print("\t");
  Serial.print(a2_val);Serial.print("\t");
  Serial.print(a3_val);Serial.print("\t");
  Serial.print(a4_val);Serial.println("\t");
  if(a1_val == 0 && a2_val == 1 && a3_val == 1 && a4_val ==1)
  {
    
    digitalWrite(ZW_B1,HIGH);
    motors.motorControl(M1,255);
    motors.motorControl(M2,255);      
  }

  else if(a1_val == 1 && a2_val == 0 && a3_val == 1 && a4_val == 1) 
  {
     
    digitalWrite(ZW_B2,HIGH);
    motors.motorControl(M1,-255);
    motors.motorControl(M2,-255);
  
  }
  else if(a1_val == 1 && a2_val == 1 && a3_val == 0 && a4_val == 1) 
  {
   
    digitalWrite(ZW_B3,HIGH);
    motors.motorControl(M3,255);
    motors.motorControl(M4,255);
  
  }
   else if(a1_val == 1 && a2_val == 1 && a3_val == 1 && a4_val == 0) 
  {
   
    digitalWrite(ZW_B4,HIGH);
    motors.motorControl(M3,-255);
    motors.motorControl(M4,-255);
  
  }
  else
  {
    digitalWrite(ZW_B1,LOW);
    digitalWrite(ZW_B2,LOW);
    digitalWrite(ZW_B3,LOW);
    digitalWrite(ZW_B4,LOW);
    motors.motorControl(M1,0);
    motors.motorControl(M2,0);
    motors.motorControl(M3,0);
    motors.motorControl(M4,0);
  
  
  }
  
 
}