/*
 Controlling a servo position using a potentiometer (variable resistor)

*/

#include <Servo.h>
#include <StarterPro.h>


Servo myservo;  // create servo object to control a servo

int potpin = ZW_A1;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin

void setup() {
  myservo.attach(ZW_B1);  // attaches the servo on pin ZW_B1/ZW_B2/ZW_B3/ZW_B4 to the servo object
}

void loop() {
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  myservo.write(val);                  // sets the servo position according to the scaled value
  delay(15);                           // waits for the servo to get there
}
