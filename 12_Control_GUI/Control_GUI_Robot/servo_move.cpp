#include "servo_move.h"
/******************
Left1 S0-S1  S12  S7-S6   Right1
            \ | /      
Left2 S2-S3 —— —— S9-S8   Right2
            /   \
Left3 S4-S5       S11-S10 Right3
********************/

int angle[SERVO_NUM] = {ANGLE0,ANGLE1,ANGLE2,ANGLE3,ANGLE4,ANGLE5,ANGLE6,ANGLE7,ANGLE8,ANGLE9,ANGLE10,ANGLE11,ANGLE12};
Servo myservo[SERVO_NUM];

bool isMoveing = 0;

void Servo_Setup(void)
{
  // Attach all servos to their respective pins
  int servoPins[SERVO_NUM] = {S0, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12};

  for(int i = 0;i<SERVO_NUM;i++) {
    myservo[i].attach(servoPins[i]);
    myservo[i].write(angle[i]);
  }
}

void Servo_Angle(int servo_id, int angle)
{
  if (servo_id >= SERVO_NUM || servo_id < 0)
    return;
  angle = constrain(angle, 0, 180);
  myservo[servo_id].write(angle);
}

void moveStop()
{
  isMoveing = 0;
  for(int i = 0;i<SERVO_NUM;i++)
    myservo[i].write(angle[i]);
}



void moveForward() 
{
  //Lift the first set of legs and step forward.
  if(!isMoveing) {
    isMoveing = 1;
    for (int i = 0; i <= STEP_ANGLE; i++) {
      myservo[0].write(angle[0] - i*2);
      myservo[4].write(angle[4] - i*2);
      myservo[8].write(angle[8] + i*2);

      myservo[1].write(angle[1] + i);
      myservo[5].write(angle[5] + i);
      myservo[9].write(angle[9] - i);

      myservo[3].write(angle[3] - i);
      myservo[7].write(angle[7] + i);
      myservo[11].write(angle[11] + i);

      delay(stepDelay);
    }
  }
  else {
    for (int i = 0; i <= STEP_ANGLE; i++) {
      myservo[0].write(angle[0] - i*2);
      myservo[4].write(angle[4] - i*2);
      myservo[8].write(angle[8] + i*2);

      myservo[1].write(angle[1] -STEP_ANGLE + i*2);
      myservo[5].write(angle[5] -STEP_ANGLE + i*2);
      myservo[9].write(angle[9] +STEP_ANGLE - i*2);

      myservo[3].write(angle[3] + STEP_ANGLE - i*2);
      myservo[7].write(angle[7] - STEP_ANGLE + i*2);
      myservo[11].write(angle[11] - STEP_ANGLE + i*2);
      delay(stepDelay);
    }
  }

  //Lower the first set of legs.
  for (int i = 0; i <= STEP_ANGLE; i++) {
    myservo[0].write(angle[0] - STEP_ANGLE*2 + i*2);
    myservo[4].write(angle[4] - STEP_ANGLE*2 + i*2);
    myservo[8].write(angle[8] + STEP_ANGLE*2 - i*2);
    delay(stepDelay/4);
  }

  //Lift the second set of legs and step forward, while simultaneously swinging the first set of legs backward.
  for (int i = 0; i <= STEP_ANGLE; i++) {
    myservo[2].write(angle[2] - i*2);
    myservo[6].write(angle[6] + i*2);
    myservo[10].write(angle[10] + i*2);

    myservo[3].write(angle[3] -STEP_ANGLE + i*2);
    myservo[7].write(angle[7] +STEP_ANGLE - i*2);
    myservo[11].write(angle[11] +STEP_ANGLE - i*2);

    myservo[1].write(angle[1] + STEP_ANGLE - i*2);
    myservo[5].write(angle[5] + STEP_ANGLE - i*2);
    myservo[9].write(angle[9] - STEP_ANGLE + i*2);
    delay(stepDelay);
  }

  //Lower the second set of legs.
  for (int i = 0; i <= STEP_ANGLE; i++) {
    myservo[2].write(angle[2] - STEP_ANGLE*2 + i*2);
    myservo[6].write(angle[6] + STEP_ANGLE*2 - i*2);
    myservo[10].write(angle[10] + STEP_ANGLE*2 - i*2);
    delay(stepDelay/4);
  }
}


void moveBackward() 
{
  if(!isMoveing) {
    for (int i = 0; i <= STEP_ANGLE; i++) {
      myservo[0].write(angle[0] - i*2);
      myservo[4].write(angle[4] - i*2);
      myservo[8].write(angle[8] + i*2);

      myservo[1].write(angle[1] - i);
      myservo[5].write(angle[5] - i);
      myservo[9].write(angle[9] + i);

      myservo[3].write(angle[3] + i);
      myservo[7].write(angle[7] - i);
      myservo[11].write(angle[11] - i);

      delay(stepDelay);
    }
  }
  else {
    for (int i = 0; i <= STEP_ANGLE; i++) {
      myservo[0].write(angle[0] - i*2);
      myservo[4].write(angle[4] - i*2);
      myservo[8].write(angle[8] + i*2);

      myservo[1].write(angle[1] +STEP_ANGLE - i*2);
      myservo[5].write(angle[5] +STEP_ANGLE - i*2);
      myservo[9].write(angle[9] -STEP_ANGLE + i*2);

      myservo[3].write(angle[3] - STEP_ANGLE + i*2);
      myservo[7].write(angle[7] + STEP_ANGLE - i*2);
      myservo[11].write(angle[11] + STEP_ANGLE - i*2);
      delay(stepDelay);
    }
  }

  for (int i = 0; i <= STEP_ANGLE; i++) {
    myservo[0].write(angle[0] - STEP_ANGLE*2 + i*2);
    myservo[4].write(angle[4] - STEP_ANGLE*2 + i*2);
    myservo[8].write(angle[8] + STEP_ANGLE*2 - i*2);
    delay(stepDelay/4);
  }

  for (int i = 0; i <= STEP_ANGLE; i++) {
    myservo[2].write(angle[2] - i*2);
    myservo[6].write(angle[6] + i*2);
    myservo[10].write(angle[10] + i*2);

    myservo[3].write(angle[3] +STEP_ANGLE - i*2);
    myservo[7].write(angle[7] -STEP_ANGLE + i*2);
    myservo[11].write(angle[11] -STEP_ANGLE + i*2);

    myservo[1].write(angle[1] - STEP_ANGLE + i*2);
    myservo[5].write(angle[5] - STEP_ANGLE + i*2);
    myservo[9].write(angle[9] + STEP_ANGLE - i*2);
    delay(stepDelay);
  }

  for (int i = 0; i <= STEP_ANGLE; i++) {
    myservo[2].write(angle[2] - STEP_ANGLE*2 + i*2);
    myservo[6].write(angle[6] + STEP_ANGLE*2 - i*2);
    myservo[10].write(angle[10] + STEP_ANGLE*2 - i*2);
    delay(stepDelay/4);
  }
}


void turnLeft() 
{
  if(!isMoveing) {
    isMoveing = 1;
    for (int i = 0; i <= STEP_ANGLE; i++) {
      myservo[0].write(angle[0] - i*2);
      myservo[4].write(angle[4] - i*2);
      myservo[8].write(angle[8] + i*2); 

      myservo[1].write(angle[1] - i);
      myservo[5].write(angle[5] - i);
      myservo[9].write(angle[9] - i);

      myservo[3].write(angle[3] + i);
      myservo[7].write(angle[7] + i);
      myservo[11].write(angle[11] + i);

      delay(stepDelay);
    }
  }
  else {
    for (int i = 0; i <= STEP_ANGLE; i++) {
      myservo[0].write(angle[0] - i*2);
      myservo[4].write(angle[4] - i*2);
      myservo[8].write(angle[8] + i*2);

      myservo[1].write(angle[1] +STEP_ANGLE - i*2);
      myservo[5].write(angle[5] +STEP_ANGLE - i*2);
      myservo[9].write(angle[9] +STEP_ANGLE - i*2);

      myservo[3].write(angle[3] - STEP_ANGLE + i*2);
      myservo[7].write(angle[7] - STEP_ANGLE + i*2);
      myservo[11].write(angle[11] - STEP_ANGLE + i*2);
      delay(stepDelay);
    }
  }

  for (int i = 0; i <= STEP_ANGLE; i++) {
    myservo[0].write(angle[0] - STEP_ANGLE*2 + i*2);
    myservo[4].write(angle[4] - STEP_ANGLE*2 + i*2);
    myservo[8].write(angle[8] + STEP_ANGLE*2 - i*2);
    delay(stepDelay/4);
  }

  for (int i = 0; i <= STEP_ANGLE; i++) {
    myservo[2].write(angle[2] - i*2);
    myservo[6].write(angle[6] + i*2);
    myservo[10].write(angle[10] + i*2);

    myservo[3].write(angle[3] +STEP_ANGLE - i*2);
    myservo[7].write(angle[7] +STEP_ANGLE - i*2);
    myservo[11].write(angle[11] +STEP_ANGLE - i*2);

    myservo[1].write(angle[1] - STEP_ANGLE + i*2);
    myservo[5].write(angle[5] - STEP_ANGLE + i*2);
    myservo[9].write(angle[9] - STEP_ANGLE + i*2);
    delay(stepDelay);
  }

  for (int i = 0; i <= STEP_ANGLE; i++) {
    myservo[2].write(angle[2] - STEP_ANGLE*2 + i*2);
    myservo[6].write(angle[6] + STEP_ANGLE*2 - i*2);
    myservo[10].write(angle[10] + STEP_ANGLE*2 - i*2);
    delay(stepDelay/4);
  }
}

void turnRight() 
{
  if(!isMoveing) {
    isMoveing = 1;
    for (int i = 0; i <= STEP_ANGLE; i++) {
      myservo[0].write(angle[0] - i*2);
      myservo[4].write(angle[4] - i*2);
      myservo[8].write(angle[8] + i*2); 

      myservo[1].write(angle[1] + i);
      myservo[5].write(angle[5] + i);
      myservo[9].write(angle[9] + i);

      myservo[3].write(angle[3] - i);
      myservo[7].write(angle[7] - i);
      myservo[11].write(angle[11] - i);

      delay(stepDelay);
    }
  }
  else {
    for (int i = 0; i <= STEP_ANGLE; i++) {
      myservo[0].write(angle[0] - i*2);
      myservo[4].write(angle[4] - i*2);
      myservo[8].write(angle[8] + i*2);

      myservo[1].write(angle[1] -STEP_ANGLE + i*2);
      myservo[5].write(angle[5] -STEP_ANGLE + i*2);
      myservo[9].write(angle[9] -STEP_ANGLE + i*2);

      myservo[3].write(angle[3] + STEP_ANGLE - i*2);
      myservo[7].write(angle[7] + STEP_ANGLE - i*2);
      myservo[11].write(angle[11] + STEP_ANGLE - i*2);
      delay(stepDelay);
    }
  }

  for (int i = 0; i <= STEP_ANGLE; i++) {
    myservo[0].write(angle[0] - STEP_ANGLE*2 + i*2);
    myservo[4].write(angle[4] - STEP_ANGLE*2 + i*2);
    myservo[8].write(angle[8] + STEP_ANGLE*2 - i*2);
    delay(stepDelay/4);
  }

  for (int i = 0; i <= STEP_ANGLE; i++) {
    myservo[2].write(angle[2] - i*2);
    myservo[6].write(angle[6] + i*2);
    myservo[10].write(angle[10] + i*2);

    myservo[3].write(angle[3] -STEP_ANGLE + i*2);
    myservo[7].write(angle[7] -STEP_ANGLE + i*2);
    myservo[11].write(angle[11] -STEP_ANGLE + i*2);

    myservo[1].write(angle[1] + STEP_ANGLE - i*2);
    myservo[5].write(angle[5] + STEP_ANGLE - i*2);
    myservo[9].write(angle[9] + STEP_ANGLE - i*2);
    delay(stepDelay);
  }

  for (int i = 0; i <= STEP_ANGLE; i++) {
    myservo[2].write(angle[2] - STEP_ANGLE*2 + i*2);
    myservo[6].write(angle[6] + STEP_ANGLE*2 - i*2);
    myservo[10].write(angle[10] + STEP_ANGLE*2 - i*2);
    delay(stepDelay/4);
  }
}

void setAngleData(int angle0, int angle2, int angle4, int angle6, int angle8, int angle10)
{
  angle[0] = angle0; angle[2] = angle2; angle[4] = angle4;
  angle[6] = angle6; angle[8] = angle8; angle[10] = angle10;
}

bool selfBalanced(float agx, float agy, float agz)
{
  int angle0, angle2, angle4, angle6, angle8, angle10;
  if(agx > BALANCED_THRESHOLD && agy > -BALANCED_THRESHOLD && agy < BALANCED_THRESHOLD) { //前倾  
    angle0 = constrain(angle[0]+3, ANGLE0 - 50, ANGLE0);
    angle4 = constrain(angle[4]-3, ANGLE4 - 50, ANGLE4);
    angle6 = constrain(angle[6]-3, ANGLE6, ANGLE6 + 50);
    angle10 = constrain(angle[10]+3, ANGLE10, ANGLE10 + 50);
  }
  else if(agx < -BALANCED_THRESHOLD && agy > -BALANCED_THRESHOLD && agy < BALANCED_THRESHOLD) { //后倾
    angle0 = constrain(angle[0]-3, ANGLE0 - 50, ANGLE0);
    angle4 = constrain(angle[4]+3, ANGLE4 - 50, ANGLE4);
    angle6 = constrain(angle[6]+3, ANGLE6, ANGLE6 + 50);
    angle10 = constrain(angle[10]-3, ANGLE10, ANGLE10 + 50);
  }
  else if(agx > -BALANCED_THRESHOLD && agx < BALANCED_THRESHOLD && agy > BALANCED_THRESHOLD) { //左倾
    angle0 = constrain(angle[0]+5, ANGLE0 - 50, ANGLE0);
    angle4 = constrain(angle[4]+5, ANGLE4 - 50, ANGLE4);
    angle6 = constrain(angle[6]+5, ANGLE6, ANGLE6 + 50);
    angle10 = constrain(angle[10]+5, ANGLE10, ANGLE10 + 50);
  }
  else if(agx > -BALANCED_THRESHOLD && agx < BALANCED_THRESHOLD && agy < -BALANCED_THRESHOLD) { //右倾
    angle0 = constrain(angle[0]-5, ANGLE0 - 50, ANGLE0);
    angle4 = constrain(angle[4]-5, ANGLE4 - 50, ANGLE4);
    angle6 = constrain(angle[6]-5, ANGLE6, ANGLE6 + 50);
    angle10 = constrain(angle[10]-5, ANGLE10, ANGLE10 + 50);
  }
  else if(agx > BALANCED_THRESHOLD && agy > BALANCED_THRESHOLD) { //左前倾
    angle0 = constrain(angle[0]+3, ANGLE0 - 50, ANGLE0);
    angle4 = constrain(angle[4]-2, ANGLE4 - 30, ANGLE4);
    angle6 = constrain(angle[6]+2, ANGLE6, ANGLE6 + 30);
    angle10 = constrain(angle[10]+3, ANGLE10, ANGLE10 + 50);
  }
  else if(agx > BALANCED_THRESHOLD && agy < -BALANCED_THRESHOLD) { //右前倾
    angle0 = constrain(angle[0]-2, ANGLE0 - 30, ANGLE0);
    angle4 = constrain(angle[4]-3, ANGLE4 - 50, ANGLE4);
    angle6 = constrain(angle[6]-3, ANGLE6, ANGLE6 + 50);
    angle10 = constrain(angle[10]+2, ANGLE10, ANGLE10 + 30);
  }
  else if(agx < -BALANCED_THRESHOLD && agy > BALANCED_THRESHOLD) { //左后倾
    angle0 = constrain(angle[0]-2, ANGLE0 - 30, ANGLE0);
    angle4 = constrain(angle[4]+3, ANGLE4 - 50, ANGLE4);
    angle6 = constrain(angle[6]+3, ANGLE6, ANGLE6 + 50);
    angle10 = constrain(angle[10]+2, ANGLE10, ANGLE10 + 30);
  }
  else if(agx < -BALANCED_THRESHOLD && agy < -BALANCED_THRESHOLD) { //右后倾
    angle0 = constrain(angle[0]-3, ANGLE0 - 50, ANGLE0);
    angle4 = constrain(angle[4]-2, ANGLE4 - 30, ANGLE4);
    angle6 = constrain(angle[6]+2, ANGLE6, ANGLE6 + 30);
    angle10 = constrain(angle[10]-3, ANGLE10, ANGLE10 + 50);
  }
  else
    return true;

  float hight2 = (6.0*cos((ANGLE0-angle0)* PI / 180.0)+6.0*cos((ANGLE4-angle4)* PI / 180.0))/2.0;
  angle2 = ANGLE2 - acos(hight2 / 6.0) * 180.0 / PI;
  float hight8 = (6.0*cos((angle6-ANGLE6)* PI / 180.0)+6.0*cos((angle10-ANGLE10)* PI / 180.0))/2.0;
  angle8 = ANGLE8 + acos(hight8 / 6.0) * 180.0 / PI;
  
  setAngleData(angle0, angle2, angle4, angle6, angle8, angle10); 

  if(!isMoveing) {
    for(int i = 0;i<SERVO_NUM;i=i+2)
      myservo[i].write(angle[i]);
  }
  return false;
}

void restore(){
  setAngleData(ANGLE0, ANGLE2, ANGLE4, ANGLE6, ANGLE8, ANGLE10); 
  for(int i = 0;i<SERVO_NUM;i++) {
    myservo[i].write(angle[i]);
  }
}
