#include "Adeept_Hexpod_For_Arduino.h"

// //////////////////////Buzzer drive area///////////////////////////////////
int tune_song[] = {0, G4, G4, A4, G4, C5, B4, G4, G4, A4, G4, D5, C5, G4, G4, C5, B4, C5, B4, A4, F5, F5, B4, C5, D5, C5, //birthday_song
                   0, C4, C4, G4, G4, A4, A4, G4, F4, F4, E4, E4, D4, D4, C4, G4, G4, F4, F4, E4, E4, D4, G4, G4, F4, F4, E4, E4, D4, C4, C4, G4, G4, A4, A4, G4, F4, F4, E4, E4, D4, D4, C4 //star_song
                  };
int durt_song[] = {2000 ,300, 300, 300, 300, 300, 600, 300, 300, 300, 300, 300, 600, 300, 300, 300, 300, 300, 300, 600, 300, 300, 300, 300, 300, 600, //birthday_song
                   2000, 300, 300, 300, 300, 300, 300, 600, 300, 300, 300, 300, 300, 300, 600, 300, 300, 300, 300, 300, 300, 600, 300, 300, 300, 300, 300, 300, 600, 300, 300, 300, 300, 300, 300, 600, 300, 300, 300, 300, 300, 300, 600 //star_song
                  };

void Buzzer_Setup(void)
{
  pinMode(PIN_BUZZER, OUTPUT);
  delay(10);
  noTone(PIN_BUZZER); //stop vocalizing
}

//Buzzer alarm function
void Buzzer_Alert(int beat, int rebeat)
{
  beat = constrain(beat, 1, 9);
  rebeat = constrain(rebeat, 1, 255);
  for (int j = 0; j < rebeat; j++){
    for (int i = 0; i < beat; i++){
      tone(PIN_BUZZER, BUZZER_FREQUENCY);
      delay(100);
      noTone(PIN_BUZZER); //stop vocalizing
      delay(100);
    }
    delay(500);
  }
}

void Buzzer_Silence()
{
  noTone(PIN_BUZZER); //stop vocalizing
}

//Buzzer playsong function
void Buzzer_PlaySong()
{
  static int i = 0;
  static unsigned long previousMillis = 0;

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= durt_song[i])
  {
    previousMillis = currentMillis;
    i++;
    if(i>=sizeof(tune_song) / sizeof(tune_song[0]))
      i = 0;
    tone(PIN_BUZZER, tune_song[i]); 
  }
}

/////////////////////WS2812 LED area///////////////////////////////////
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void WS2812_Setup() 
{
  strip.begin();         // Initialize the NeoPixel library.
  strip.setBrightness(50); // Set WS2812 LED brightness.
}
void WS2812_Brightness(int Brightness) 
{
  strip.setBrightness(Brightness); // Set WS2812 LED brightness.
}

void WS2812Color(int num, int R, int G, int B)
{
  strip.setPixelColor(num,strip.Color(R,G,B));
  strip.show();    
}

void WS2812ColorAll(int R, int G, int B)
{
    for(int i=0; i<=LED_COUNT; i++){
      strip.setPixelColor(i,strip.Color(R,G,B));
  }
  strip.show();  
}

void breathingEffect(int r, int g, int b) 
{
  static int brightness = 0;
  static int fadeAmount = 10;
  static unsigned long previousMillis = 0;

  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= 100) {
    previousMillis = currentMillis;
    
    brightness += fadeAmount;
    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount;
    }
    
    int currR = map(brightness, 0, 255, 0, r);
    int currG = map(brightness, 0, 255, 0, g);
    int currB = map(brightness, 0, 255, 0, b);
    
    for(int i = 0; i < LED_COUNT; i++) {
      strip.setPixelColor(i, strip.Color(currR, currG, currB));
    }
    strip.show();
  }
}

uint32_t Wheel(byte WheelPos) 
{
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
void rainbowEffect() 
{
  static unsigned long previousMillis = 0;
  static int hue = 0;

  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= 100) {
    previousMillis = currentMillis;
    
    for(int i = 0; i < LED_COUNT; i++) {
      int pixelHue = (hue + i * 32) % 256;
      strip.setPixelColor(i, Wheel(pixelHue));
    }
    
    strip.show();
    hue = (hue + 1) % 256;
  }
}

void runningLightEffect(int r, int g, int b) 
{
  static unsigned long previousMillis = 0;
  static int position = 0;
  static int direction = 1;

  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= 300) {
    previousMillis = currentMillis;
    
    strip.clear();
    
    strip.setPixelColor(position, strip.Color(r, g, b));
    
    int prev1 = position - direction;
    int prev2 = position - 2*direction;
    
    if (prev1 >= 0 && prev1 < LED_COUNT) {
      strip.setPixelColor(prev1, strip.Color(r/3, g/3, b/3));
    }
    if (prev2 >= 0 && prev2 < LED_COUNT) {
      strip.setPixelColor(prev2, strip.Color(r/6, g/6, b/6));
    }
    
    strip.show();
    
    position += direction;
    if (position <= 0 || position >= LED_COUNT - 1) {
      direction = -direction;
    }
  }
}

void alarmEffect(int r, int g, int b) 
{
  static unsigned long previousMillis = 0;
  static int state = 0;

  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= 300) {
    previousMillis = currentMillis;
    
    state = (state + 1) % 4;
    strip.clear();
    
    switch(state) {
      case 0: // 全亮
        for(int i = 0; i < LED_COUNT; i++) {
          strip.setPixelColor(i, strip.Color(r, g, b));
        }
        break;
      case 1: // 奇数亮
        for(int i = 0; i < LED_COUNT; i++) {
          if (i % 2 == 1) {
            strip.setPixelColor(i, strip.Color(r, g, b));
          }
        }
        break;
      case 2: // 全灭
        strip.clear();
        break;
      case 3: // 偶数亮
        for(int i = 0; i < LED_COUNT; i++) {
          if (i % 2 == 0) {
            strip.setPixelColor(i, strip.Color(r, g, b));
          }
        }
        break;
    }
    
    strip.show();
  }
}

/////////////////////ultrasonic area///////////////////////////////////
void Ultrasonic_Setup() 
{
  Wire.begin();         // Initialize I2C communication
}

uint32_t getDistance() 
{
  Wire.beginTransmission(HCSR04_I2C_ADDR);
  Wire.write(0x01); // Usually write 0x01 command to start
  byte error = Wire.endTransmission();
  
  if (error != 0) {
    Wire.beginTransmission(HCSR04_I2C_ADDR);
    Wire.write(0x01); // Usually write 0x01 command to start
    byte error = Wire.endTransmission();
  }
  delay(50);  //Wait for the measurement to complete (the module needs time to measure)

  Wire.requestFrom(HCSR04_I2C_ADDR, 3);// Read data. Usually 3 bytes[1,4]
  if (Wire.available() >= 3) {
    byte highByte = Wire.read();   // High byte of distance data
    byte midByte = Wire.read();    // Middle byte of distance data
    byte lowByte = Wire.read();    // Low byte of distance data
    // Combine the 3 bytes into a complete distance value (usually in millimeters)
    uint32_t dist = ( ((uint32_t)highByte << 16) + ((uint32_t)midByte << 8) + lowByte ) /1000 /10.0;
    return dist;
  }
  return 0;
}

/////////////////////OLED area///////////////////////////////////
SSD1306AsciiWire oled;

void OLED_Setup() 
{
  Wire.begin();
  oled.begin(&Adafruit128x64, OLED_I2C_ADDR);
  oled.setFont(Adafruit5x7);
  oled.clear();
}
  
void OLED_clear()
{
  oled.clear();
}
  
void OLED(int font, int x, int y, char text[])
{
  if(font == 1){
    oled.set1X();
  } else {
    oled.set2X();
  }
  
  oled.setCursor(x,y); // (x,y)
  oled.print(text);
  oled.println(); 
}

////////////////////Battery area/////////////////////////////////////
//Gets the battery ADC value
int Get_Battery_Voltage_ADC(void)
{
  //pinMode(PIN_BATTERY, INPUT);
  int batteryADC = 0;
  for (int i = 0; i < 5; i++)
    batteryADC += analogRead(PIN_BATTERY);
  return batteryADC / 5;
}

//Get the battery voltage value
float Get_Battery_Voltage(void)
{
  int batteryADC = Get_Battery_Voltage_ADC();
  float batteryVoltage = ((float)batteryADC/(float)1023) * 5 * 2;
  if(batteryVoltage >= 8.4){
    batteryVoltage = 8.4;
    }
  return batteryVoltage;
}
float baseVoltage = 6;
int Get_Battery_ratio(void)
{
  float voltage = Get_Battery_Voltage();
  return (voltage - baseVoltage)*100/(8.4 - baseVoltage) ;
}
