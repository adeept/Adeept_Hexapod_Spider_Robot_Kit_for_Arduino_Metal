#ifndef __SERVO_MOVE_H__
#define __SERVO_MOVE_H__
#include <Arduino.h>
#include <Servo.h>
#include "angle.h"
#define S0 4   
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
#define SERVO_NUM 13
/******************
S0-S1  S12  S7-S6
      \ | /      
S2-S3 —— —— S9-S8
      /   \
S4-S5       S11-S10
********************/
#define BALANCED_THRESHOLD 1.5 //平衡角度阈值 
#define STEP_ANGLE 20  //步幅的一半
#define stepDelay  12

void Leg(int Hip_id, int Hip_angle, int Knee_id, int Knee_angle);
void Servo_Setup(void);
void Servo_Angle(int servo_id, int angle);
void moveStop();
void moveForward();
void moveBackward();
void turnLeft();
void turnRight();
bool selfBalanced(float agx, float agy, float agz); //平衡返回true，非平衡返回false
void restore();
#endif
