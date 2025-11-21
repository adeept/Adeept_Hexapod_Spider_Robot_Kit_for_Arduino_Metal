  /**********************************************************************
  Product     : Adeept Hexpod for Arduino
  Auther      : www.adeept.com
  Modification: 2025/10/20
**********************************************************************/
#include "Adeept_Hexpod_For_Arduino.h" 
#include "mpu6050.h"
#include "servo_move.h"

#define Move_UP "forward"
#define Move_Down "backward"
#define Move_Left "left"
#define Move_Right "right"
#define Move_Stop "DTS"
#define Head_Left "lookleft"
#define Head_Right "lookright"
#define Head_LRStop "LRStop"
#define MOVE_FORWARD 1
#define MOVE_BACKWARD 2
#define TURN_LEFT 3
#define TURN_RIGHT 4
#define MOVE_STOP 0
int move_flag = 0; //0 indicates stop, 1 indicates move forward, 2 indicates move backward, 3 indicates turning left, and 4 indicates turning right.

int hand_Angle = ANGLE12;
int stat_hand = 0; //0 indicates no rotation, 1 indicates turning left, and 2 indicates turning right.

#define Auto_Matic 1
#define Auto_Matic_ON "automatic"
#define Auto_Matic_OFF "automaticOff"
#define Keep_Distance 2
#define Keep_Distance_ON "keepDistance"
#define Keep_Distance_OFF "keepDistanceOff"
#define Function_OFF 0
int function_flag = Function_OFF;
       
#define BREATHING   0       // breathing light
#define RAINBOW     1       // rainbow light
#define RUNNING     2       // running light
#define ALARM       3       // alarm light
int ws2812Mode = -1; 
int r = 0, g = 0, b = 0; 

#define AVOID_DIST  40 // cm
#define MIN_DIST  20 // cm
float midDist;
float leftDist;
float rightDist;

int stat_steady = 0;
int buzzer_flag = 0; 
float agx,agy,agz;
String comdata = "";


void setup()
{
  Serial.begin(115200);       // set up a wifi serial communication baud rate 115200
  
  Serial.println("AT+CWMODE=3\r\n");//set to softAP+station mode
  delay(3000);     //delay 3s  
  Serial.println("AT+CWSAP=\"Adeept_ADA033\",\"12345678\",8,2\r\n");   //TCP Protocol, server IP addr, port
  delay(1000);     //delay 1s
  Serial.println("AT+RST\r\n");     //reset wifi
  delay(1000);     //delay 1s
  Serial.println("AT+CIPMUX=1\r\n");//set to multi-connection mode
  delay(1000);
  Serial.println("AT+CIPSERVER=1,4000\r\n");//set as server
  delay(1000);
  Serial.println("AT+CIPSTO=7000\r\n");//keep the wifi connecting 7000 seconds
  delay(1000);

  Servo_Setup();               //Servo initialization
  Mpu6050_Setup();              //Mpu6050 initialization

  Buzzer_Setup();                //Buzzer initialization
  Buzzer_Alert(2, 1);

  WS2812_Setup();                //WS2812 LED initialization   
  WS2812ColorAll(r,g,b);

  Ultrasonic_Setup();            //Ultrasonic initialization

  OLED_Setup();                //OLED initialization
  OLED(1, 0, 0, "Adeept.com");
  OLED(1, 0, 1, "IP: 192.168.4.1");
  OLED(2, 0, 5, "NOFunction");

  delay(100);
}

void loop()
{
  while(Serial.available()>0)
  {  
    comdata += char(Serial.read());
    delay(1);
  }
  judgement();
  control();
  delay(1);
  show_Battery_ratio();
}


void judgement()
{
  if (comdata.length() > 0){ 
    //Serial.println(comdata);
    // OLED_clear();
    // OLED(1, 0, 0, comdata.c_str());
    if(comdata.indexOf(Head_LRStop)>=0){
      stat_hand = 0;
    }
    else if(comdata.indexOf(Head_Left)>=0){//head trun left
      stat_hand = 1;
    }
    else if(comdata.indexOf(Head_Right)>=0){//head trun right
      stat_hand = 2;
    }

    else if(comdata.indexOf(Move_Stop)>=0){//move stop
      move_flag = MOVE_STOP;
      moveStop();
    }
    else if(comdata.indexOf(Move_UP)>=0){//move forward
      move_flag = MOVE_FORWARD;
    }
    else if(comdata.indexOf(Move_Down)>=0){//move backward
      move_flag = MOVE_BACKWARD;
    }
    else if(comdata.indexOf(Move_Left)>=0){//trun left
      move_flag = TURN_LEFT;
    }
    else if(comdata.indexOf(Move_Right)>=0){//trun right
      move_flag = TURN_RIGHT;
    }

    else if(comdata.indexOf(Auto_Matic_OFF)>=0 || comdata.indexOf(Keep_Distance_OFF)>=0)
    {
      function_flag = Function_OFF;
      moveStop();
      OLED(2, 0, 5, "NOFunction");
    }
    else if(comdata.indexOf(Auto_Matic_ON)>=0)
    {
      Buzzer_Silence();
      hand_Angle =  ANGLE12;
      function_flag = Auto_Matic;
      OLED(2, 0, 5, "Auto Matic");
    }
    else if(comdata.indexOf(Keep_Distance_ON)>=0)
    {
      Buzzer_Silence();
      hand_Angle =  ANGLE12;
      function_flag = Keep_Distance;
      OLED(2, 0, 5, "Keep Dstnc");
    }

    else if (comdata.indexOf("lightMode")>0)
    {
      String dataArrayString = comdata.substring(comdata.indexOf("["), comdata.indexOf("]"));
      int firstComma = dataArrayString.indexOf(",");
      int secondComma = dataArrayString.indexOf(",", firstComma + 1);
      r = dataArrayString.substring(1, firstComma).toInt();
      g = dataArrayString.substring(firstComma + 1, secondComma).toInt();
      b = dataArrayString.substring(secondComma + 1).toInt();
      if(comdata.indexOf("breath")>0){
        ws2812Mode = BREATHING;
      }
      else if(comdata.indexOf("flowing")>0){
        ws2812Mode = RUNNING;
      }
      else if(comdata.indexOf("rainbow")>0){
        ws2812Mode = RAINBOW;
      }
      else if(comdata.indexOf("police")>0){
        ws2812Mode = ALARM;
      }
    } 

    else if(comdata.indexOf("Buzzer_Music_Off")>0){
      buzzer_flag = 0;
      Buzzer_Silence();
    }
    else if(comdata.indexOf("Buzzer_Music")>0){
      buzzer_flag = 1;
    }

    else if(comdata.indexOf("steadyOff")>0){
      OLED(2, 0, 2, "        ");
      stat_steady = 0;
      restore();
    }
    else if(comdata.indexOf("steady")>0){
      OLED(2, 0, 2, "Balanced");
      stat_steady = 1;
    }

    comdata = "";
  }
}

void control()
{
  if(stat_hand && !function_flag) 
  {
    if(stat_hand == 1 && hand_Angle<180)
      hand_Angle ++;
    else if(stat_hand == 2  && hand_Angle>0)
      hand_Angle --;
    Servo_Angle(12, hand_Angle);
    delay(10);
  }

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

  if(buzzer_flag && !function_flag) 
    Buzzer_PlaySong();

  if(stat_steady && !move_flag && !function_flag) 
  {
    getOffsetAngle(agx,agy,agz);
    selfBalanced(agx, agy, agz);
  }
}

void Avoid_Obstacles()
{
  Servo_Angle(12, hand_Angle);
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
