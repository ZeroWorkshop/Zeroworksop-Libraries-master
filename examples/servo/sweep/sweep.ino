/* Sweep

 This example code is in the public domain.

*/

#include <Servo.h>
#include <StarterPro.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

int delay_interval  = 10;  
double time_start = 0;
double  currAngle;
double step  = 0.1;
int direction = 1;
void setup() {
  myservo.attach(ZW_B1);  // attaches the servo on pin ZW_B1/ZW_B2/ZW_B3/ZW_B4 to the servo object
  myservo.write(0);
  time_start = millis();
}

void loop() {
  
  if(currAngle >180)
  {
  	if(millis() - time_start > delay_interval)
  	{
  		 currAngle = currAngle + step * (direction);
  		 if(currAngle >180)
  		 {
  		 	 currAngle = 180;
  		 	 direction = -1;
  		 }
  		 if(currAngle < 0)
  		 {
  		 		currAngle = 0;
  		 		direction = 1;
  		 }
  		 
  		 myservo.write(currAngle);
  		 time_start = millis();
  	}
  
  }
  
}

