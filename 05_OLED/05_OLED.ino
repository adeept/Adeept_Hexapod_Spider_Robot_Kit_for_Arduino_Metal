 /*************************************
File name:OLED
Description:OLED displays text.
Website:www.addept.com
*************************************/
#include <Wire.h>
#include <SSD1306AsciiWire.h>

SSD1306AsciiWire display;

unsigned long previousMillis = 0;
const long interval = 1000; // Update every 1 second

// Initial time
char compileTime[] = __TIME__;
int hours, minutes, seconds;

void setup() {
  // Initialize OLED
  Wire.begin();
  display.begin(&Adafruit128x64, 0x3C);
  display.setFont(Adafruit5x7);
  display.clear();
  sscanf(compileTime, "%d:%d:%d", &hours, &minutes, &seconds);
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Update every second
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    // Update time
    seconds++;
    if (seconds >= 60) {
      seconds = 0;
      minutes++;
      if (minutes >= 60) {
        minutes = 0;
        hours++;
        if (hours >= 24) {
          hours = 0;
        }
      }
    }
    
    // Update display
    updateDisplay();
  }
}

void updateDisplay() {
  // Display large time
  display.set2X();
  display.setCursor(20, 0); // Center display
  
  // Format display HH:MM:SS
  if (hours < 10) display.print("0");
  display.print(hours);
  display.print(":");
  if (minutes < 10) display.print("0");
  display.print(minutes);
  display.print(":");
  if (seconds < 10) display.print("0");
  display.print(seconds);
}