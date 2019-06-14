
//Name this tab: CommandLine.h

#include <string.h>
#include <stdlib.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <StarterPro.h>
#include <ZeroMotors.h>
#include <Pushbutton.h>
#include <UltrasonicSensor.h>
#include <Servo.h>

Servo myservoB1;  // create servo object to control a servo
Servo myservoB2;  // create servo object to control a servo
Servo myservoB3;  // create servo object to control a servo
Servo myservoB4;  // create servo object to control a servo

//this following macro is good for debugging, e.g.  print2("myVar= ", myVar);
#define print2(x,y) (Serial.print(x), Serial.println(y))

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  110 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  550 // this is the 'maximum' pulse length count (out of 4096)

#define CR '\r'
#define LF '\n'
#define BS '\b'
#define NULLCHAR '\0'
#define SPACE ' '

#define COMMAND_BUFFER_LENGTH        500                       //length of serial buffer for incoming commands
char   CommandLine[COMMAND_BUFFER_LENGTH + 1];                 //Read commands into this buffer from Serial.  +1 in length for a termination char

const char *delimiters            = ", \n";                    //commands can be separated by return, space or comma
const char *delimiters2            = "#;";  
/*************************************************************************************************************
     your Command Names Here
*/
const char *ServoCommandToker    = "servo";                     //Modify here
const char *DelayCommandToken  = "delay";                     //Modify here
const char *MotorCommandToken  = "motor";

ZeroMotors motors;
Pushbutton START(ZERO_BUTTON);

/*************************************************************************************************************
    getCommandLineFromSerialPort()
      Return the string of the next command. Commands are delimited by return"
      Handle BackSpace character
      Make all chars lowercase
*************************************************************************************************************/

bool getCommandLineFromSerialPort(char * commandLine)
{
  static uint8_t charsRead = 0;                      //note: COMAND_BUFFER_LENGTH must be less than 255 chars long
  //read asynchronously until full command input
  while (Serial.available()) {
    char c = Serial.read();
    switch (c) {
      case CR:      //likely have full command in buffer now, commands are terminated by CR and/or LS
      case LF:
        commandLine[charsRead] = NULLCHAR;       //null terminate our command char array
        if (charsRead > 0)  {
          charsRead = 0;                           //charsRead is static, so have to reset
          Serial.println(commandLine);
          return true;
        }
        break;
      case BS:                                    // handle backspace in input: put a space in last char
        if (charsRead > 0) {                        //and adjust commandLine and charsRead
          commandLine[--charsRead] = NULLCHAR;
          Serial << byte(BS) << byte(SPACE) << byte(BS);  //no idea how this works, found it on the Internet
        }
        break;
      default:
        // c = tolower(c);
        if (charsRead < COMMAND_BUFFER_LENGTH) {
          commandLine[charsRead++] = c;
        }
        commandLine[charsRead] = NULLCHAR;     //just in case
        break;
    }
  }
  return false;
}


/* ****************************
   readNumber: return a 16bit (for Arduino Uno) signed integer from the command line
   readWord: get a text word from the command line

*/
int readNumber () {
  char * numTextPtr = strtok(NULL, delimiters);         //K&R string.h  pg. 250
  return atoi(numTextPtr);                              //K&R string.h  pg. 251
}

char * readWord() {
  char * word = strtok(NULL, delimiters);               //K&R string.h  pg. 250
  return word;
}

void
nullCommand(char * ptrToCommandName) {
  print2("Command not found: ", ptrToCommandName);      //see above for macro print2
}


/****************************************************
   Add your commands here
*/

int servoCommand() {                                      //Modify here
  char * servoPin = readWord();
  int servoAngle = readNumber();
  if ((strcmp(servoPin, "B1") == 0) ||  (strcmp(servoPin, "b1") == 0))
  {
    myservoB1.write(servoAngle);  
  }
  else if ((strcmp(servoPin, "B2") == 0)|| (strcmp(servoPin, "b2") == 0))
  {
    myservoB2.write(servoAngle);  
  }
  else if ((strcmp(servoPin, "B3") == 0) || (strcmp(servoPin, "b3") == 0))
  {
    myservoB3.write(servoAngle);  
  }
  else if ((strcmp(servoPin, "B4") == 0) || (strcmp(servoPin, "b4") == 0) )
  {
    myservoB4.write(servoAngle);  
  }
  else
  {
    Serial.println("ERROR: wrong port, please use port B1/B2/B3/B4 only!!!!\n");
  }
 
  
  return servoAngle;
}

int motorCommand(){
	char * motorPort = readWord();
	int motorSpeed = readNumber();

  if ((strcmp(motorPort, "M1") == 0) || (strcmp(motorPort, "m1") == 0))
  {
    motors.motorControl(M1, motorSpeed);
  }
  else if ((strcmp(motorPort, "M2") == 0) || (strcmp(motorPort, "m2") == 0))
  {
    motors.motorControl(M2, motorSpeed);
  }
  else if ((strcmp(motorPort, "M3") == 0) || (strcmp(motorPort, "m3") == 0))
  {
    motors.motorControl(M3, motorSpeed);
  }
  else if ((strcmp(motorPort, "M4") == 0) || (strcmp(motorPort, "m4") == 0))
  {
    motors.motorControl(M4, motorSpeed);
  }
  else
  {
     Serial.println("ERROR: wrong motor port, please use port M1/M2/M3/M4 only!!!!\n");
  }
  return motorSpeed;
}

int DelayCommand() {                                //Modify here
  int time_ms = readNumber();
 // int secondOperand = readNumber();
  delay(time_ms);
  return time_ms;
}

/****************************************************
   DoMyCommand
*/
bool DoMyCommand(char * commandLine) {
  //  print2("\nCommand: ", commandLine);
  int result;

  char * ptrToCommandArray[30]; 
  char * ptrCommandCurr;
  
  ptrCommandCurr = strtok(commandLine,delimiters2);
  int idx = 0;
  while( ptrCommandCurr != NULL)
  {
      ptrToCommandArray[idx]=malloc( (strlen(ptrCommandCurr)+1) * sizeof(char));
      strcpy(ptrToCommandArray[idx++],ptrCommandCurr);
      Serial.println(ptrCommandCurr);
      ptrCommandCurr = strtok(NULL,delimiters2);
  }
  Serial.print("idx = ");
  Serial.println(idx);

  for(int i = 0; i<idx; i++)
  {
    Serial.println(ptrToCommandArray[i]);
     char * ptrToCommandName = strtok(ptrToCommandArray[i], delimiters);
        print2("commandName= ", ptrToCommandName);

      if (strcmp(ptrToCommandName, ServoCommandToker) == 0) {                   //Modify here
        result = servoCommand();
       print2(">    Set Servo to  ", result);

      } else if(strcmp(ptrToCommandName, DelayCommandToken) == 0)  {           //Modify here
          result = DelayCommand();                                       //K&R string.h  pg. 251
          print2(">    delay ", result);

      } else if(strcmp(ptrToCommandName, MotorCommandToken) == 0)  {           //Modify here
          result = motorCommand();                                       //K&R string.h  pg. 251
          print2(">    motor ", result);

      } else {
        nullCommand(ptrToCommandName);
      } 
  }

  for(int i = 0; i<idx; i++)
  {
  free(ptrToCommandArray[i]);  
  }

     Serial.flush();

}
