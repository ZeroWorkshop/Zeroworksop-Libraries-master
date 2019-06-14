#include  "StarterPro.h"
#include "LineFollowerArray.h"
#include <Wire.h>
#include <SoftwareSerial.h>
#include <ZeroMotors.h>
#include <Pushbutton.h>
#include <UltrasonicSensor.h>


LineFollowerArray  LineFollower(0x09);
ZeroMotors motors;
Pushbutton START(ZERO_BUTTON);

#define  _speed_       150
#define  WHITE_LINE    1   //for white line  set to  1  or set to 0

void  followSegment();

void setup() {
  // put your setup code here, to run once:
	playPowerOn();
  LineFollower._CAL_MAX_[0] = 2000;//,2000,2000,2000,2000,2000,2000,2000};
  LineFollower._CAL_MIN_[0] = 300;//,324,296,332,372,544,496,620};
  LineFollower._CAL_MAX_[1] = 2000;//,2000,2000,2000,2000,2000,2000,2000};
  LineFollower._CAL_MIN_[1] = 300;//,324,296,332,372,544,496,620};
  LineFollower._CAL_MAX_[2] = 2000;//,2000,2000,2000,2000,2000,2000,2000};
  LineFollower._CAL_MIN_[2] = 300;//,324,296,332,372,544,496,620};
  LineFollower._CAL_MAX_[3] = 2000;//,2000,2000,2000,2000,2000,2000,2000};
  LineFollower._CAL_MIN_[3] = 300;//,324,296,332,372,544,496,620};
  LineFollower._CAL_MAX_[4] = 2000;//,2000,2000,2000,2000,2000,2000,2000};
  LineFollower._CAL_MIN_[4] = 300;//,324,296,332,372,544,496,620};
  LineFollower._CAL_MAX_[5] = 2000;//,2000,2000,2000,2000,2000,2000,2000};
  LineFollower._CAL_MIN_[5] = 300;//,324,296,332,372,544,496,620};
  LineFollower._CAL_MAX_[6] = 2000;//,2000,2000,2000,2000,2000,2000,2000};
  LineFollower._CAL_MIN_[6] = 300;//,324,296,332,372,544,496,620};
  LineFollower._CAL_MAX_[7] = 2000;//,2000,2000,2000,2000,2000,2000,2000};
  LineFollower._CAL_MIN_[7] = 300;//,324,296,332,372,544,496,620};
  LineFollower.begin();
  
  Serial.begin(115200);

  
  START.waitForButton();
  playStart();
}

void loop() {
    
  followSegment();
 
}



void followSegment()
{

  int offset_from_center;
  int power_difference;
  int left_speed, right_speed;
  int newSpeed;

  unsigned int sensors[8];
  int position;
 
  
  position =  LineFollower.readLine(sensors, WHITE_LINE);
  offset_from_center = ((int)position) - 3500;


    power_difference = offset_from_center / 20;
    if (power_difference >  _speed_)
      power_difference = _speed_;
    if (power_difference < -_speed_)
      power_difference = -_speed_;


   
    if (power_difference < 0)
    {
      left_speed = _speed_ + power_difference;
      right_speed = -_speed_;
    }
    else
    {
      left_speed = _speed_;
      right_speed =- _speed_ + power_difference;
    }
   
   
   
#if 1
    for (int i = 0; i < 8; i++)
    {

      Serial.print(sensors[i]);
      Serial.print("\t");
    }
    Serial.print(position);
    Serial.print("\t");
    Serial.print(offset_from_center);
    Serial.print("\t");
    
    Serial.print(power_difference);
    Serial.print("\t");
    Serial.print(left_speed);
    Serial.print("\t");
    Serial.println(right_speed);
#endif


   
   motors.setSpeeds(left_speed, right_speed);
}