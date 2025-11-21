#ifndef __ADEEPT_HEXPOD_H__
#define __ADEEPT_HEXPOD_H__
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <SSD1306AsciiWire.h>

// //////////////////////Buzzer drive area///////////////////////////////
//Buzzer pin definition             
#define PIN_BUZZER 3                    //Define the pins for the Arduino control buzzer
#define BUZZER_CHN 0                    //Define the PWM channel for Arduino
#define BUZZER_FREQUENCY 2000           //Define the resonant frequency of the buzzer 
#define G4 392
#define A4 440
#define B4 494
#define C5 523
#define D5 587
#define F5 698
#define C4 262
#define D4 294
#define E4 330
#define F4 349
void Buzzer_Setup(void);                //Buzzer initialization
void Buzzer_Alert(int beat, int rebeat);//Buzzer alarm function
void Buzzer_Silence();
void Buzzer_PlaySong();

/////////////////////WS2812 LED area///////////////////////////////////
#define LED_PIN    A3         // WS2812 connect to pin A3 .
#define LED_COUNT   5         // LED number.
void WS2812_Setup();
void WS2812_Brightness(int Brightness);
void WS2812Color(int num, int R, int G, int B);
void WS2812ColorAll(int R, int G, int B);
void breathingEffect(int r, int g, int b);
void rainbowEffect();
void runningLightEffect(int r, int g, int b);
void alarmEffect(int r, int g, int b);

/////////////////////ultrasonic area///////////////////////////////////
#define HCSR04_I2C_ADDR 0x57
void Ultrasonic_Setup();
uint32_t getDistance();

/////////////////////////OLED area/////////////////////////////////////
#define OLED_I2C_ADDR 0x3C
void OLED_Setup();
void OLED_clear();
void OLED(int font, int x, int y, char text[]);

/////////////////////Battery area///////////////////////////////////
#define PIN_BATTERY   A7        //Set the battery detection voltage pin 
int Get_Battery_Voltage_ADC(void);   //Gets the battery ADC value (0-1023)
float Get_Battery_Voltage(void);     //Get the battery voltage value (8.4V-6V)
int Get_Battery_ratio(void);

#endif
