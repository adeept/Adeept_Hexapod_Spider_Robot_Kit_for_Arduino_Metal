/**********************************************************************
  Description : Read battery voltage.
  Auther      : www.adeept.com
**********************************************************************/
#include <Wire.h>
#include <SSD1306AsciiWire.h>
#include "Adeept_Battery_For_Arduino.h"

SSD1306AsciiWire display;

void setup() {
  // Initialize OLED
  Wire.begin();
  Wire.setClock(400000L);
  display.begin(&Adafruit128x64, 0x3C);
  display.setFont(Adafruit5x7);
  display.clear();
}

void loop() {
  display.set1X();
  display.setCursor(0, 0); // Center display
  display.print("Bat ADC : ");
  display.print(Get_Battery_Voltage_ADC());//Gets the battery ADC value
  display.setCursor(0, 3); // Center display
  display.print("Bat Voltage : ");
  display.print(Get_Battery_Voltage());      //Get the battery voltage value
  display.print("V");
  display.setCursor(0, 6); // Center display
  display.print("Bat Level : ");
  display.print(Get_Battery_ratio());
  display.print("%");
  delay(1000);
}
