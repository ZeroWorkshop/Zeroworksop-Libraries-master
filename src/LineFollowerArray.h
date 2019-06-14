/**
 * \par Copyright (C), 206, Zeroworkshop
 * \class   StarterProI2C
 * \brief   Driver for Starter Pro module.
 * @file    StarterProI2C.h
 * @author  Zeroworkshop
 * @version V1.0.0
 * @date    2019/05/8
 * @brief   Header for StarterProI2C.cpp module
 *
 * \par Copyright
 * This software is Copyright (C), 2016-2019, Zeroworkshop. Use is subject to license \n
 * conditions. The main licensing options available are GPL V2 or Commercial: \n
 *
 * \par Open Source Licensing GPL V2
 * This is the appropriate option if you want to share the source code of your \n
 * application with everyone you distribute it to, and you also want to give them \n
 * the right to share who uses it. If you wish to use this software under Open \n
 * Source Licensing, you must contribute all your source code to the open source \n
 * community in accordance with the GPL Version 2 when your application is \n
 * distributed. See http://www.gnu.org/copyleft/gpl.html
 *
*/
#ifndef _LINEFOLLOWERARRAY_H_
#define _LINEFOLLOWERARRAY_H_

#include <Arduino.h>
#include <Wire.h>
#include <Servo.h>
#include "StarterPro.h"



/**
 * Class: MeEncoderNew
 * \par Description
 * Declaration of Class MeEncoderNew
 */
class LineFollowerArray{
public:

  long _CAL_MAX_[8] = {0,0,0,0,0,0,0,0};
  long _CAL_MIN_[8] = {5000,5000,5000,5000,5000,5000,5000,5000};
/**
 * Alternate Constructor which can call your own function to map the Encoder Motor New to arduino port,
 * you can set any slot for the Encoder Motor New device. 
 * \param[in]
 *   port - RJ25 port from PORT_1 to PORT_10
 * \param[in]
 *   slot - SLOT1 or SLOT2
 */
  LineFollowerArray(uint8_t addr);


/**
 * Alternate Constructor which can call your own function to map the Encoder Motor New to arduino port,
 * you should initialized slot and slaveAddress here for the Encoder Motor New device.
 * \param[in]
 *   None
 */
  LineFollowerArray(void);

/**
 * \par Function
 *    begin
 * \par Description
 *    Initialize Encoder Motor New.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
  void begin(void);
  
/**
 * \par Function
 *    setAddr
 * \par Description
 *     Reset the i2c address of encoder motor .
 * \param[in]
 *    i2cAddr - i2c address of encoder motor
 * \param[in]
 *    slot - slot number of encoder motor
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
  void setAddr(uint8_t i2cAddr);

/**
 * \par Function
 *    reset
 * \par Description
 *    Reset the parameter of Motor.
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
  void reset(void);
  
  

/**
 * \par Function
 *    setDevid
 * \par Description
 *    Set the devid to Motor.
 * \param[in]
 *    devid - the I2C adress
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
  void setDevid(uint8_t devid);
  
  
    
void setLineType(long line);
long GetLineType();

void setMaxVal(long max_val);
void setEmitterOn();
void setEmitterOff();
void setCalData(uint8_t sensor_id, long * max_val, long * min_val);
void getCalData(uint8_t sensor_id, long * max_val, long * min_val);
void read(long *d);
void read(uint8_t sensor_id,long * dValue);
//
void getPosition(long *data,unsigned char white_line)  ;

void readCalibrated(uint8_t sensor_id,long * dValue,unsigned char white_line);
void readCalibrated(long * sensor_value);

void resetCalibration();
int  readLine(unsigned int *sensor_values, int white_line);
int  readLine(long *sensor_values, int white_line);


void calibration();

private:
/**
 * \par Function
 *    sendCmd
 * \par Description
 *    Send command to Motor.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
  void sendCmd(void); 
 // void sendCmd(uint8_t address);
  void getLineType(long *data);  
  uint8_t _slot; 
  uint8_t address;    
  uint8_t lineType;                                                    
  unsigned long _lastTime;
  char cmdBuf[18];
  unsigned int _maxValue; // the maximum value returned by this function
  int _lastValue;
  
};





#endif






