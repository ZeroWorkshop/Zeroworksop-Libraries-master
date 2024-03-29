/**
 * \par Copyright (C), 2017-2019, 
 * @file    I2CScanTest.ino
 * @author  
 * @version V1.0.0
 * @date    
 * @brief   Description: this file is sample code for  I2C Scan.
 *
 * Function List:
 * 1. void TwoWire::begin(void)
 * 2. void    TwoWire::beginTransmission(uint8_t address)
 * 3. uint8_t TwoWire::endTransmission(void)
 *
 * \par History:
 * <pre>
 * <Author>     <Time>        <Version>      <Descr>
 * 
 * </pre>
 */
#include <Wire.h>

void setup()
{
  Wire.begin();
  Serial.begin(115200);
  Serial.println("I2C Scanner");
}

void loop()
{
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error==4) 
    {
      Serial.print("Unknow error at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
  {
    Serial.println("No I2C devices found");
  }
  else
  {
    Serial.println("done");
  }
  delay(5000);    // wait 5 seconds for next scan
}
