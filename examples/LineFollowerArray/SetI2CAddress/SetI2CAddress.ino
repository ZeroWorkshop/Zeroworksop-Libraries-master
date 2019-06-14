#include "LineFollowerArray.h"
#include "StarterPro.h"
#include <Wire.h>
#include <SoftwareSerial.h>

#define  DEFAULT_I2C_ADDR   0x09
#define  New_I2C_ADDR   	  0x10

LineFollowerArray  LineFollower(DEFAULT_I2C_ADDR);



void setup() {
  // put your setup code here, to run once:
  playPowerOn();
  LineFollower.begin();
  //LineFollower.setMaxVal(2000);
  LineFollower.setDevid(New_I2C_ADDR);  //use this function to change the I2C slave address of the module. and please reset the module and use I2C scan test to check the new I2C address.
  Serial.begin(115200);
  playStart();
}

void loop() {
 
}