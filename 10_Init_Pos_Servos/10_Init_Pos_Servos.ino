/***********************************************************
File name: Servo.ino
Website: www.adeept.com
E-mail: support@adeept.com
***********************************************************/
#include <Servo.h>
#define S0 4   //Define servo0 interface digital interface 4
#define S1 5   
#define S2 6   
#define S3 7   
#define S4 8   
#define S5 9   
#define S6 10   
#define S7 11   
#define S8 12   
#define S9 13   
#define S10 A0   
#define S11 A1   
#define S12 A2   

#define LEG_NUM 13
Servo myservo[LEG_NUM];

void setup() {
  // Attach all servos to their respective pins
  myservo[0].attach(S0);  // Attach servo0 to pin S0
  myservo[1].attach(S1);  // Attach servo1 to pin S1
  myservo[2].attach(S2);  // Attach servo2 to pin S2
  myservo[3].attach(S3);  // Attach servo3 to pin S3
  myservo[4].attach(S4);  // Attach servo4 to pin S4
  myservo[5].attach(S5);  // Attach servo5 to pin S5
  myservo[6].attach(S6);  // Attach servo6 to pin S6
  myservo[7].attach(S7);  // Attach servo7 to pin S7
  myservo[8].attach(S8);  // Attach servo8 to pin S8
  myservo[9].attach(S9);  // Attach servo9 to pin S9
  myservo[10].attach(S10); // Attach servo10 to pin S10
  myservo[11].attach(S11); // Attach servo11 to pin S11
  myservo[12].attach(S12); // Attach servo12 to pin S12

  // Initialize all servos to 90 degrees
  for(int i = 0; i < LEG_NUM; i++)
    myservo[i].write(90);
}

void loop() {
}
