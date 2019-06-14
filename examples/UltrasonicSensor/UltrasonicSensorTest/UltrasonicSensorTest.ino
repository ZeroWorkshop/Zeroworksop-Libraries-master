/**
 * \par Copyright (C), 2012-2016, 
 * @file    UltrasonicSensorTest.ino
 * @author  
 * @version V1.0.0
 * @date    
 * @brief   Description: this file is sample code for Me ultrasonic sensor module.
 *
 * Function List:
 * 1. double MeUltrasonicSensor::distanceCm(uint16_t MAXcm)
 *
 * \par History:
 * <pre>
 * <Author>     <Time>        <Version>      <Descr>
 *
 * </pre>
 */
#include "UltrasonicSensor.h"
#include "StarterPro.h"

UltrasonicSensor ultraSensor(ZW_A1);

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  Serial.print("Distance : ");
  Serial.print(ultraSensor.distanceCm() );
  Serial.println(" cm");
  delay(100); /* the minimal measure interval is 100 milliseconds */
}

