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

#include "LineFollowerArray.h"

// move state and function
#define CMD_RESET         0x00

#define CMD_SET_CAL_DATA  0x14
#define CMD_SET_EMITTER   0x15
#define CMD_SET_MAX_VAL   0x16
#define CMD_SET_DEVID     0x17
#define CMD_SET_LINE_TYPE 0x18

#define CMD_GET_CAL_DATA        0x24
#define CMD_GET_POSITION_DATA   0x26
#define CMD_GET_FINAL_DATA      0x27
#define CMD_GET_RAW_DATA        0x28
#define CMD_GET_LINE_TYPE       0x29
#define I2C_DEFAULT_ADDR        0x9

//#define I2C_DEFAULT_ADDR        0x9


/**
 * Alternate Constructor which can call your own function to map the Encoder Motor New to arduino port,
 * you can set any slot for the Encoder Motor New device. 
 * \param[in]
 *   port - RJ25 port from PORT_1 to PORT_10
 * \param[in]
 *   slot - SLOT1 or SLOT2
 */
LineFollowerArray::LineFollowerArray(uint8_t addr)
{
  address = addr;
  _slot = 1;
  _maxValue = 2500;
}



/**
 * Alternate Constructor which can call your own function to map the Encoder Motor New to arduino port,
 * you should initialized slot and slaveAddress here for the Encoder Motor New device.
 * \param[in]
 *   None
 */
LineFollowerArray::LineFollowerArray(void)
{
  address = 0x09;
  _slot = 1;
  _maxValue = 2500;
}



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
void LineFollowerArray::begin(void)
{
  Wire.begin();
}



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
void LineFollowerArray::setAddr(uint8_t i2cAddr)
{
  address = i2cAddr;
}


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
void LineFollowerArray::reset(void)
{
  cmdBuf[0] = _slot;
  cmdBuf[1] = CMD_RESET;
  sendCmd();
  delay(2);
}



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
void LineFollowerArray::sendCmd(void)
{
  Wire.beginTransmission(address); 
  for(int i=0;i<18;i++)
    Wire.write(cmdBuf[i]);       
  Wire.endTransmission();
}



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
void LineFollowerArray::setDevid(uint8_t devid)
{
  cmdBuf[0] = _slot;
  cmdBuf[1] = CMD_SET_DEVID;
  cmdBuf[2] = devid;
  sendCmd();
}



void LineFollowerArray::setLineType(long line)
{
  cmdBuf[0] = _slot;
  cmdBuf[1] = CMD_SET_LINE_TYPE;
  memcpy(cmdBuf+2,&line,4);
  sendCmd();
}


void LineFollowerArray::getLineType(long *data)
{
  long raw_value;
  char buf[4];
  Wire.beginTransmission(address);
  Wire.write(_slot);
  Wire.write(CMD_GET_LINE_TYPE);
  Wire.endTransmission(0);
  Wire.requestFrom(address,(uint8_t)4);

  for(int i=0;i<4;i++)
  {
    buf[i] = Wire.read();
  }
  *data = *(long*)buf;
}
 
 long LineFollowerArray::GetLineType()
 {
    long value;
    getLineType(&value); 
    return value;
}


void LineFollowerArray::setEmitterOn()
{
  cmdBuf[0] = _slot;
  cmdBuf[1] = CMD_SET_EMITTER;
  cmdBuf[2] = 0x1;
  sendCmd();
}

void LineFollowerArray::setEmitterOff()
{
  cmdBuf[0] = _slot;
  cmdBuf[1] = CMD_SET_EMITTER;
  cmdBuf[2] = 0x1;
  sendCmd();
  
}


void LineFollowerArray::setMaxVal(long max_val)
{
  _maxValue = max_val;
  cmdBuf[0] = _slot;
  cmdBuf[1] = CMD_SET_MAX_VAL;
  memcpy(cmdBuf+2,&max_val,4);
  sendCmd();
  
}

void LineFollowerArray::setCalData(uint8_t sensor_id, long * max_val, long * min_val)
{
  cmdBuf[0] = sensor_id;
  cmdBuf[1] = CMD_SET_CAL_DATA;
  memcpy(cmdBuf+2,&max_val,4);
  memcpy(cmdBuf+6,&min_val,4);
  sendCmd();
  delay(10);
}

void LineFollowerArray::getCalData(uint8_t sensor_id, long * max_val, long * min_val)
{
   char buf[8];
  Wire.beginTransmission(address);
  Wire.write(sensor_id);
  Wire.write(CMD_GET_CAL_DATA);
  Wire.endTransmission(0);
  Wire.requestFrom(address,(uint8_t)8);
  for(int i=0;i<4;i++)
  {
    buf[i] = Wire.read();
  }
  *max_val = *(long*)buf;
  for(int i=0;i<4;i++)
  {
    buf[i] = Wire.read();
  }
  *min_val = *(long*)buf;
}

void LineFollowerArray::read(long *d)
{
  long raw_value;
  _slot = 0;
  char buf[8];
  Wire.beginTransmission(address);
  Wire.write(_slot);
  Wire.write(CMD_GET_RAW_DATA);
  Wire.endTransmission(0);
  Wire.requestFrom(address,(uint8_t)32);

  for(int j = 0;j<8;j++)
  {
  for(int i=0;i<4;i++)
  {
    buf[i] = Wire.read();
  }
  *(d+j) = *(long*)buf;

 //  Serial.print( *(d+j));
  //  Serial.print(" ");
  }
  //Serial.println();
 // delayMicroseconds(1000);
}

    
void LineFollowerArray::read(uint8_t sensor_id,long * dValue)
{
  long raw_value;
  char buf[8];
  Wire.beginTransmission(address);
  Wire.write(sensor_id);
  Wire.write(CMD_GET_RAW_DATA);
  Wire.endTransmission(0);
  Wire.requestFrom(address,(uint8_t)4);
  for(int i=0;i<4;i++)
  {
    buf[i] = Wire.read();
  }
  *dValue = *(long*)buf;
    
 // return raw_value;
}

    

void LineFollowerArray::getPosition(long *data,unsigned char white_line = 0)
{
  long raw_value;
  char buf[8];
  Wire.beginTransmission(address);
  Wire.write(_slot);
  Wire.write(CMD_GET_POSITION_DATA);
  Wire.endTransmission(0);
  Wire.requestFrom(address,(uint8_t)4);

  for(int i=0;i<4;i++)
  {
    buf[i] = Wire.read();
  }
  *data = *(long*)buf;

  if(white_line)
  *data = 7000 - *data; 
}


      

void LineFollowerArray::readCalibrated(uint8_t sensor_id,long * dValue,unsigned char white_line = 0)
{
  long raw_value;
  char buf[8];
  Wire.beginTransmission(address);
  Wire.write(sensor_id);
  Wire.write(CMD_GET_FINAL_DATA);
  Wire.endTransmission(0);
  Wire.requestFrom(address,(uint8_t)4);
  for(int i=0;i<4;i++)
  {
    buf[i] = Wire.read();
  }
  *dValue = *(long*)buf;
  if(white_line)
  *dValue = 1000- *dValue;  
 // return raw_value;
}

/*        
void LineFollowerArray::readCalibrated(long * dValue,unsigned char white_line = 0)
{
  long raw_value;
  char buf[8];
  _slot = 0;
  Wire.beginTransmission(address);
  Wire.write(_slot);
  Wire.write(CMD_GET_FINAL_DATA);
  Wire.endTransmission(0);
  Wire.requestFrom(address,(uint8_t)4);
  
  
   for(int j = 0;j<8;j++)
  {
    for(int i=0;i<4;i++)
    {
    buf[i] = Wire.read();
    }
   *(dValue+j) = *(long*)buf;
    if(white_line)
   *(dValue+j) = 1000 - *(dValue+j);
  }
 
}      */
    
    
void LineFollowerArray::calibration()
{

    long sensor_raw_data[8];  
    read(sensor_raw_data);
    for(int i = 0; i<8; i++)
    {
        //Serial.print(sensor_raw_data[i]);
        //Serial.print("\t");
        if(_CAL_MAX_[i]< sensor_raw_data[i]) _CAL_MAX_[i] = sensor_raw_data[i];
        if(_CAL_MIN_[i]> sensor_raw_data[i]) _CAL_MIN_[i] = sensor_raw_data[i];
    }
  // Serial.println();
}  


void LineFollowerArray::resetCalibration()
{
    unsigned char i;
    for(i=0;i<8;i++)
    {
        _CAL_MAX_[i] = 0; 
        _CAL_MIN_[i] = _maxValue;    
      //  setCalData(i+1,_CAL_MAX_[i],_CAL_MIN_[i]); 
    }

}

void LineFollowerArray::readCalibrated(long * sensor_values)
{
    unsigned int calmin,calmax;
    unsigned int denominator;
    long sensor_raw_data[8];  
    read(sensor_raw_data);
    for(int i = 0; i<8; i++)
    {
        calmin = _CAL_MIN_[i];
        calmax = _CAL_MAX_[i];
        denominator = calmax - calmin; 
        
        signed int x = 0;
        if(denominator != 0)
            x = (((signed long)sensor_raw_data[i]) - calmin)* 1000 / denominator;
        if(x < 0)
            x = 0;
        else if(x > 1000)
            x = 1000;
        sensor_values[i] = x;
        //Serial.print(sensor_raw_data[i]);
        //Serial.print("\t");
    }
    //Serial.println();
   
}



int LineFollowerArray::readLine(long *sensor_values,int white_line)
{
    unsigned char i, on_line = 0;
    unsigned long avg; // this is for the weighted total, which is long
                       // before division
    unsigned int sum; // this is for the denominator which is <= 64000
    long sensor_raw_data[8];  
    readCalibrated(sensor_raw_data);

    avg = 0;
    sum = 0;

    for(i=0;i<8;i++) {
        //sensor_values[i] =   sensor_raw_data[i];
        int value = sensor_raw_data[i];
        if(white_line)
        {
          value = 1000-value;  
        }
        sensor_values[i]= value;
        // keep track of whether we see the line at all
        if(value > 200) {
            on_line = 1;
        }

        // only average in values that are above a noise threshold
        if(value > 50) {
            avg += (long)(value) * (i * 1000);
            sum += value;
        }
    }

    if(!on_line)
    {
        // If it last read to the left of center, return 0.
        if(_lastValue < (8-1)*1000/2)
            return 0;

        // If it last read to the right of center, return the max.
        else
            return (8-1)*1000;

    }

    _lastValue = avg/sum;

    return _lastValue;
}

int LineFollowerArray::readLine(unsigned int *sensor_values,int white_line)
{
    unsigned char i, on_line = 0;
    unsigned long avg; // this is for the weighted total, which is long
                       // before division
    unsigned int sum; // this is for the denominator which is <= 64000
    long sensor_raw_data[8];  
    readCalibrated(sensor_raw_data);

    avg = 0;
    sum = 0;

    for(i=0;i<8;i++) {
        //sensor_values[i] =   sensor_raw_data[i];
        int value = sensor_raw_data[i];
        if(white_line)
        {
          value = 1000-value;  
        }
        sensor_values[i]= value;
        // keep track of whether we see the line at all
        if(value > 200) {
            on_line = 1;
        }

        // only average in values that are above a noise threshold
        if(value > 50) {
            avg += (long)(value) * (i * 1000);
            sum += value;
        }
    }

    if(!on_line)
    {
        // If it last read to the left of center, return 0.
        if(_lastValue < (8-1)*1000/2)
            return 0;

        // If it last read to the right of center, return the max.
        else
            return (8-1)*1000;

    }

    _lastValue = avg/sum;

    return _lastValue;
}
