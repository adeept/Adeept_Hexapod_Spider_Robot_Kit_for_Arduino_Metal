#include <Wire.h> // Import the Arduino I2C library
#include <SSD1306AsciiWire.h>

// Set the I2C address according to the module manual, commonly 0x57 or 0x70
#define HCSR04_I2C_ADDR 0x57

SSD1306AsciiWire display;

void setup() {
  Serial.begin(115200);   // Initialize the serial port for outputting distance data
  Wire.begin();         // Initialize I2C communication
  delay(100);           // Give the module some time to start up

  display.begin(&Adafruit128x64, 0x3C);
  display.setFont(Adafruit5x7);
  display.clear();
  display.set2X();
  Serial.println("HC-SR04 I2C Mode Distance Measurement");
}

void loop() {
  uint32_t distance_mm = getDistance();
  
  if (distance_mm == 0) {
    Serial.println("Measurement error or timeout.");
  } else {
    display.setCursor(0, 0); // Center display
    display.print("Distance: ");
    display.setCursor(0, 3); // Center display
    display.print(distance_mm); // Output distance in millimeters
    display.println(" cm  ");
  }
  delay(200); // At least 200ms interval between two measurements[1](@ref)
}

// Function to get distance via I2C
uint32_t getDistance() {
  // 1. Send measurement command
  Wire.beginTransmission(HCSR04_I2C_ADDR);
  Wire.write(0x01); // Usually write 0x01 command to start ranging[1,4](@ref)
  byte error = Wire.endTransmission();
  
  if (error != 0) {
    // Serial.print("I2C transmission error: ");
    // Serial.println(error);
    Wire.beginTransmission(HCSR04_I2C_ADDR);
    Wire.write(0x01); // Usually write 0x01 command to start ranging[1,4](@ref)
    byte error = Wire.endTransmission();
  }
  
  // 2. Wait for the measurement to complete (the module needs time to measure)
  delay(50); // Blocking delay, simple handling. Can be changed to non-blocking if needed
  
  // 3. Read data. Usually 3 bytes[1,4](@ref)
  Wire.requestFrom(HCSR04_I2C_ADDR, 3);
  if (Wire.available() >= 3) {
    byte highByte = Wire.read();   // High byte of distance data
    byte midByte = Wire.read();    // Middle byte of distance data
    byte lowByte = Wire.read();    // Low byte of distance data
    
    // Combine the 3 bytes into a complete distance value (usually in millimeters)
    
      uint32_t dist = ( ((uint32_t)highByte << 16) + ((uint32_t)midByte << 8) + lowByte ) /1000;
    
    return dist/10.0;
  } else {
    Serial.println("Incomplete data received.");
    return 0;
  }
}
