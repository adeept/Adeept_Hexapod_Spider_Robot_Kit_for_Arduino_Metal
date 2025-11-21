  /**********************************************************************
  Product     : Adeept Hexpod for Arduino
  Auther      : www.adeept.com
  Modification: 2025/10/20
**********************************************************************/
#include <IRremote.hpp>
#include "Adeept_Hexpod_For_Arduino.h" 
#include "mpu6050.h"
#include "servo_move.h"

#define RECV_PIN   2        // Infrared receiving pin

#define Move_UP 12 //key "up"
#define Move_Down 13 //key "down"
#define Move_Left 14 //key "left"
#define Move_Right 15 //key "right"
#define Move_Stop 16 //key "ok"
#define Head_Left 1 //key "1"
#define Head_Right 3 //key "3"
#define MOVE_FORWARD 1
#define MOVE_BACKWARD 2
#define TURN_LEFT 3
#define TURN_RIGHT 4
#define MOVE_STOP 0
int move_flag = 0; //0 indicates stop, 1 indicates move forward, 2 indicates move backward, 3 indicates turning left, and 4 indicates turning right.

int hand_Angle = ANGLE12;

#define Auto_Matic_ON 4 //key "4"
#define Keep_Distance_ON 6 //key "6"
#define Auto_Matic 1
#define Keep_Distance 2
#define Function_OFF 0
int function_flag = Function_OFF;

#define Steady_ON 10 //key "*"
#define Steady_OFF 11 //key "#"

#define BREATHING   0       // 呼吸灯
#define RAINBOW     1       // 彩虹灯
#define RUNNING     2       // 流水灯
#define ALARM       3       // 警报灯
int ws2812Mode = -1; 
int r = 0, g = 0, b = 0; 

#define AVOID_DIST  40 // cm
#define MIN_DIST  20 // cm
float midDist;
float leftDist;
float rightDist;

int stat_steady = 0;
float agx,agy,agz;
int comdata = -1;

void setup()
{  
  // Buzzer_Setup();                //Buzzer initialization
  // Buzzer_Alert(2, 1);

  IR_Setup();
  delay(100);  
  Servo_Setup();               //Servo initialization
  delay(100);   
  Mpu6050_Setup();              //Mpu6050 initialization

  WS2812_Setup();                //WS2812 LED initialization   
  WS2812ColorAll(r,g,b);

  Ultrasonic_Setup();            //Ultrasonic initialization

  OLED_Setup();                //OLED initialization
  OLED(1, 0, 0, "Adeept.com");
  OLED(2, 0, 5, "NOFunction");

  delay(100);    
}

void loop()
{
  if (IrReceiver.decode()) {          // Waiting for decoding
    comdata = getIRValue();
  }
  judgement();
  control();
  delay(1);
  show_Battery_ratio();
}

void judgement()
{
  // char buffer[2];
  // sprintf(buffer, "%d", comdata); // 将整数转换为字符串
  // OLED(1, 0, 0, buffer);
  if(comdata == Move_UP){//move forward
    move_flag = MOVE_FORWARD;
  }
  else if(comdata == Move_Down){//move backward
    move_flag = MOVE_BACKWARD;
  }
  else if(comdata == Move_Left){//trun left
    move_flag = TURN_LEFT;
  }
  else if(comdata == Move_Right){//trun right
    move_flag = TURN_RIGHT;
  }
  else if(comdata == Move_Stop){//move stop
    function_flag = Function_OFF;
    move_flag = MOVE_STOP;
    moveStop();
    OLED(2, 0, 5, "NO Function");
  }

  else if(comdata == Head_Left){//head trun left
    hand_Angle += 3;
    if(hand_Angle > 180)
    {
      hand_Angle = 180;
    }
    Servo_Angle(12, hand_Angle);
  }
  else if(comdata == Head_Right){//head trun right
    hand_Angle -= 3;
    if(hand_Angle < 0)
    {
      hand_Angle = 0;
    }
    Servo_Angle(12, hand_Angle);
  }

  else if(comdata == Auto_Matic_ON)
  {
    hand_Angle =  ANGLE12;
    function_flag = Auto_Matic;
    OLED(2, 0, 5, "Auto Matic");
  }
  else if(comdata == Keep_Distance_ON)
  {
    Servo_Angle(12, hand_Angle);
    hand_Angle =  ANGLE12;
    function_flag = Keep_Distance;
    OLED(2, 0, 5, "Keep Dstnc");
  }

  else if(comdata == 5){
    ws2812Mode = BREATHING;
    r = 255, g = 255, b = 0;
  }
  else if(comdata == 7){
    ws2812Mode = RUNNING;
    r = 0, g = 255, b = 255;
  }
  else if(comdata == 8){
    ws2812Mode = RAINBOW;
    r = 255, g = 0, b = 255;
  }
  else if(comdata == 9){
    ws2812Mode = ALARM;
    r = 255, g = 0, b = 0;
  }
  else if(comdata == 0){
    ws2812Mode = -1;
    WS2812ColorAll(0,0,0);
  }

  else if(comdata == Steady_OFF){
    OLED(2, 0, 2, "        ");
    stat_steady = 0;
    restore();
  }
  else if(comdata == Steady_ON){
    OLED(2, 0, 2, "Balanced");
    stat_steady = 1;
  }

  comdata = -1;
}

void control()
{
  switch (move_flag) 
  {
    case MOVE_FORWARD:
      moveForward();
      break;
    case MOVE_BACKWARD:
      moveBackward();
      break;
    case TURN_LEFT:
      turnLeft();
      break;
    case TURN_RIGHT:
      turnRight();
      break;
  }

  switch (function_flag) 
  {
    case Auto_Matic:
      Avoid_Obstacles();
      break;
    case Keep_Distance:
      Ultrasonic_Follow();
      break;
  }

  switch(ws2812Mode) 
  {
    case BREATHING:
      breathingEffect(r, g, b);
      break;
    case RAINBOW:
      rainbowEffect();
      break;
    case RUNNING:
      runningLightEffect(r, g, b);
      break;
    case ALARM:
      alarmEffect(r, g, b);
      break;
  }

  if(stat_steady && !move_flag && !function_flag) 
  {
    getOffsetAngle(agx,agy,agz);
    selfBalanced(agx, agy, agz);
  }
}

void Avoid_Obstacles()
{
  midDist = getDistance();
  
  if (midDist > AVOID_DIST){
    moveForward();
  }
  else if (midDist <= MIN_DIST)
  {
    moveBackward();
  }
  else {
    moveStop();
    Servo_Angle(12, hand_Angle + 45); // left distance.
    delay(300);
    leftDist = getDistance();
    Servo_Angle(12, hand_Angle - 45); // right distance.
    delay(300);
    rightDist = getDistance();
    Servo_Angle(12, hand_Angle); // back to mid.

    if (leftDist >= rightDist){
      for(int i=0; i<2; i++)
      {
        turnLeft();
      }
    }
    else{ 
      for(int i=0; i<2; i++)
      {
        turnRight();
      }
    }
  }
}

void Ultrasonic_Follow()
{
  uint32_t distance = getDistance();
  if (distance < 30){
    moveBackward();
  }
  else if (distance > 40){
    moveForward();
  }
  else {
    moveStop();
  }
  delay(10);
}

int show_Battery_ratio()
{
  static unsigned long previousMillis = -60000;
  char buffer[4];
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= 60000) {
    previousMillis = currentMillis;

    sprintf(buffer, "%d%%", Get_Battery_ratio()); // 将整数转换为字符串
    OLED(1, 110, 0, buffer);
  }
}

////////////////////////IR area/////////////////////////////////
void IR_Setup()
{
  IrReceiver.begin(RECV_PIN);        // Start the receiver
}

int switch_irr(unsigned long irr_data)
{
  switch(irr_data)
  {
    case 0x19: return 0;
    case 0x45: return 1;
    case 0x46: return 2;
    case 0x47: return 3;
    case 0x44: return 4;
    case 0x40: return 5;
    case 0x43: return 6;
    case 0x7: return 7;
    case 0x15: return 8;
    case 0x9: return 9;
    case 0x16: return 10; // *
    case 0xD: return 11; // #
    case 0x18: return 12; // up
    case 0x52: return 13; // down
    case 0x8: return 14; // left
    case 0x5A: return 15; // right
    case 0x1C: return 16; // ok
  }
}

int getIRValue()
{
  unsigned long value = IrReceiver.decodedIRData.command;
  value = switch_irr(value);
  IrReceiver.resume();                        // Release the IRremote. Receive the next value
  return value;
}
