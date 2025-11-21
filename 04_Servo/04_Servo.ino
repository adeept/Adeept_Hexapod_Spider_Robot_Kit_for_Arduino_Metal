/***********************************************************
File name: Servo.ino
Website: www.adeept.com
E-mail: support@adeept.com
***********************************************************/
#include <Servo.h>
int servoPin1 = 4;    //Define servo interface digital

Servo servo1;

void setup() {
  // put your setup code here, to run once:
  pinMode(servoPin1,OUTPUT);//Set the servo interface as the output interface
  
  servo1.attach(servoPin1);
}

void loop()
{
  servo1.write(0);  // Set servo 1 to turn to 0 degrees.
  delay(1000);      // delay 1s.
  servo1.write(90); // 90 degrees,servo have angular deviation
  delay(1000);
  servo1.write(180); // 180 degrees.
  delay(1000);
}
