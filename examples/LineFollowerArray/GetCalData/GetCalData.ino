#include "LineFollowerArray.h"
#include <Wire.h>
#include <SoftwareSerial.h>

LineFollowerArray  LineFollower(0x09);

void setup() {
  // put your setup code here, to run once:
  LineFollower.begin();
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
  //LineFollower.setMaxVal(2000);
  Serial.begin(115200);
}

void loop() {
  long sensors[8];  
  
  int position;
  
  position =  LineFollower.readLine(sensors, 1);
  
  
  for(int i = 0; i<8; i++)
  {  
        Serial.print(sensors[i]);
        Serial.print("\t");
  }  
    Serial.println(); 

  /// LineFollower.calibration();
    
}