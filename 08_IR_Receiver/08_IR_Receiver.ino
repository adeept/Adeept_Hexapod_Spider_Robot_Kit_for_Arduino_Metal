/**********************************************************************
  Filename    : 07_IR_Receiver.ino
  Auther      : www.adeept.com
**********************************************************************/
#include <Wire.h>
#include <SSD1306AsciiWire.h>
#include <IRremote.hpp> //Call the library corresponding to the infrared remote control.
SSD1306AsciiWire display;
#define RECV_PIN     2        // Infrared receiving pin

void setup()
{
  // Initialize OLED
  Wire.begin();
  Wire.setClock(400000L);
  display.begin(&Adafruit128x64, 0x3C);
  display.setFont(Adafruit5x7);
  display.clear();

  Serial.begin(115200);       // Initialize the serial port and set the baud rate to 115200
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);        // Start the receiver
  Serial.print("IRrecvDemo is now running and waiting for IR message on Pin ");
  Serial.println(RECV_PIN);   //print the infrared receiving pin
}

void loop()
{
  if (IrReceiver.decode()) {          // Waiting for decoding
    unsigned long value = IrReceiver.decodedIRData.command;
    value = switch_irr(value);
    Serial.println(value);
    display.set2X();
    display.setCursor(0, 0); // Center display
    display.print("Receive:");
    display.print(value);
    display.print(" ");
    IrReceiver.resume();                        // Release the IRremote. Receive the next value
  }
  delay(100);
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
