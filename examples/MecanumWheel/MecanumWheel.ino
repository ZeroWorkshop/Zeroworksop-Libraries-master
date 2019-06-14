
#include "StarterProI2C.h"
#include <Wire.h>
#include <SoftwareSerial.h>
#include  "StarterPro.h"
#include <ZeroMotors.h>
#include <Pushbutton.h>
#include <Adafruit_PWMServoDriver.h>

StarterProI2C  StarterPro_STEPPER(0x09);

#define  _speed_  255
#define SERVOMIN  110 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  550 // this is the 'maximum' pulse length count (out of 4096)

ZeroMotors motors;
Pushbutton START(ZERO_BUTTON);

double angle_zero = 0;
double angle_one = 0;
double angle_two = 0;
double angle_three = 0;
double angle_four = 0;
double angle_five = 0;
double angle_six = 0;
double angle_seven = 0;
double step = 0.1;
// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver servo = Adafruit_PWMServoDriver();
uint8_t servonum = 0;
void setServoPulse(uint8_t n, double pulse);
void setServoAngle(uint8_t servoNum,double angle);
void setup() {
  // put your setup code here, to run once:
 
  
   playPowerOn();
   Serial.begin(115200);
   StarterPro_STEPPER.begin();
   servo.begin();
   servo.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
   servo.setPWM(0,0,SERVOMIN);
   servo.setPWM(1,0,SERVOMIN);
   START.waitForButton();  // need to press start button   
   playStart();
    
}

void loop() {
  // put your main code here, to run repeatedly:
  /*
    *  M1   --  0b1000
    *  M2   --  0b0100    
    *  M3   --  0b0010    
    *  M4   --  0b0001   *
    *
     */
  // StarterPro_S1.motorControl(0b1000,FORWARD,200);

  
if ( _ButtonUp)
  {
    motors.motorControl(M1,_speed_);
    motors.motorControl(M3,_speed_);
    motors.motorControl(M2,-_speed_);
    motors.motorControl(M4,-_speed_);
  }
  else if( _ButtonDown)
  {
    motors.motorControl(M1,-_speed_);
    motors.motorControl(M3,-_speed_);
    motors.motorControl(M2,_speed_);
    motors.motorControl(M4,_speed_);
  }
  else if(_ButtonLeft)
  {
    motors.motorControl(M1,-_speed_);
    motors.motorControl(M3,-_speed_);
    motors.motorControl(M2,-_speed_);
    motors.motorControl(M4,-_speed_);
  }
  else if(_ButtonRight)
  {
    motors.motorControl(M1,_speed_);
    motors.motorControl(M3,_speed_);
    motors.motorControl(M2,_speed_);
    motors.motorControl(M4,_speed_);
  }
   else if(_ButtonSquare)
  {
    motors.motorControl(M1,_speed_);
    motors.motorControl(M3,-_speed_);
    motors.motorControl(M2,_speed_);
    motors.motorControl(M4,-_speed_);
    
   } 
  else if(_ButtonCircle)
  { 
    motors.motorControl(M1,-_speed_);
    motors.motorControl(M3,_speed_);
    motors.motorControl(M2,-_speed_);
    motors.motorControl(M4,_speed_);
   } 
   else
 {
    motors.motorControl(M1,0);
    motors.motorControl(M2,0);
    motors.motorControl(M3,0);
    motors.motorControl(M4,0);
 }

//丝杆
 /* if(_ButtonL1)
   {
    StarterPro_STEPPER.stepperControl(M1M2,400,1);
   }
   else if(_ButtonL2)
   {
     StarterPro_STEPPER.stepperControl(M1M2,400,-1);
   }

   else if(_ButtonR1)
   {
     StarterPro_STEPPER.stepperControl(M3M4,400,1);
   }
   else if(_ButtonR2)
   {
     StarterPro_STEPPER.stepperControl(M3M4,400,-1);
   }
 */

 
//舵机0  
    if(_ButtonL1)
   {
      angle_zero = angle_zero + step;
   }
    else if(_ButtonL2)
   {
      angle_zero = angle_zero - step;
   }
 //舵机1
   if( _ButtonR1)
   {
    angle_one  = angle_one + step;
    }
   else if( _ButtonR2)
   {
      angle_one = angle_one - step;
   }


   
  setServoAngle(0,angle_zero);
  setServoAngle(1,angle_one);
  
}



void setServoAngle(uint8_t servoNum,double angle)
{
   int val;
   double angle_tmp;
   angle_tmp = constrain(angle, 0, 180);  
   val = map(angle_tmp,0,180,SERVOMIN,SERVOMAX);
   servo.setPWM(servoNum,0,val);
}

