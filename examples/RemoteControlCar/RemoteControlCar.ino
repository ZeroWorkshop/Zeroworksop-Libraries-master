
#include <Wire.h>
#include <SoftwareSerial.h>
#include  "StarterPro.h"
#include <ZeroMotors.h>
#include <Pushbutton.h>

ZeroMotors motors;
Pushbutton START(ZERO_BUTTON);

#define _INCLUDE_RF_CONTROLLER_ 



void setup() {
  // put your setup code here, to run once:
   playPowerOn();
   Serial.begin(115200);
   START.waitForButton();  // need to press start button   
   playStart();
}
void loop() {


if ( _ButtonUp)
  {
    motors.forward(255);
  }
  else if( _ButtonDown)
  {
   motors.backward(255);
  }
  else if(_ButtonLeft)
  {
    motors.turnLeft();
  }
  else if(_ButtonRight)
  {
     motors.turnRight();
  }
  else
 {
    motors.stop();
 }
  
}