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
// BOF preprocessor bug prevent - insert me on top of your arduino-code

#ifndef _STARTERPRO_H_
#define _STARTERPRO_H_


//#ifdef  _INCLUDE_RF_CONTROLLER_  
 extern int Rx_Buffer[6];  

void serialEvent();
//#endif 


#include <Arduino.h>
#include <Wire.h>
#include <Servo.h>
/****************************************************************/
/******  PIN DEFINITION FOR Starter Pro with I2C CPU BOARD ******/
/****************************************************************/

#define ZW_A1 A0
#define ZW_A2 A1
#define ZW_A3 A4
#define ZW_A4 A5

#define ZW_B1 A2
#define ZW_B2 A3
#define ZW_B3 2
#define ZW_B4 7

#define MOTOR1P 3
#define MOTOR1M 13
#define MOTOR2P 5
#define MOTOR2M 12
#define MOTOR3P 11
#define MOTOR3M 10
#define MOTOR4P 6
#define MOTOR4M 9

#define START_BUTTON 4
#define BEEP 8


#define  FORWARD  0
#define BACKWARD  1
#define STOP      2

#define POSITIVE 1
#define NEGATIVE -1
#define DEBUG 0


 
#define M1   0b1000
#define M2   0b0100
#define M3   0b0010
#define M4   0b0001

#define M1M2  0b1100
#define M1M3  0b1010
#define M1M4  0b1001

#define M2M3  0b0110
#define M2M4  0b0101

#define M3M4  0b0011

#define M1M2M3  0b1110
#define M1M2M4  0b1101
#define M1M3M4  0b1011
#define M2M3M4  0b0111

#define M1M2M3M4  0b1111

/****************************************************************/
/****************  PS2 REMOTE CONTROL DATA **********************/
/****************  USING SERIAL EVENT ***************************/
/****************************************************************/
#define _ButtonUp        (0x10 & Rx_Buffer[2])
#define _ButtonRight     (0x20 & Rx_Buffer[2])
#define _ButtonDown      (0x40 & Rx_Buffer[2])
#define _ButtonLeft      (0x80 & Rx_Buffer[2])
#define _ButtonTriangle  (0x10 & Rx_Buffer[3])
#define _ButtonCircle    (0x20 & Rx_Buffer[3])
#define _ButtonCross     (0x40 & Rx_Buffer[3])
#define _ButtonSquare    (0x80 & Rx_Buffer[3])
#define _ButtonL1        (0x4 & Rx_Buffer[3])
#define _ButtonL2        (0x1 & Rx_Buffer[3])
#define _ButtonR1        (0x8 & Rx_Buffer[3])
#define _ButtonR2        (0x2 & Rx_Buffer[3])
#define _ButtonSelect    (0x1 & Rx_Buffer[2])
#define _ButtonStart     (0x8 & Rx_Buffer[2])




void playNote(int Note, int Meter, int Length);
void playNoteShort(int Note, int Meter, int Length);
void playSong(int songSelected); 
void playStart(); 
void playPowerOn();

#endif






