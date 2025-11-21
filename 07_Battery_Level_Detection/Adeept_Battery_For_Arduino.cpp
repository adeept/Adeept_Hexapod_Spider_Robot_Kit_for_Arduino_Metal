#include <Arduino.h>
#include "Adeept_Battery_For_Arduino.h"

////////////////////Battery drive area/////////////////////////////////////
float batteryVoltage = 0;       //Battery voltage variable
int R1 = 100;
int R2 = 100;
float baseVoltage = 6;

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
  batteryVoltage = ((float)batteryADC/(float)1023) * 5 * 2;
  if(batteryVoltage >= 8.4){
    batteryVoltage = 8.4;
  }
  return batteryVoltage;
}

int Get_Battery_ratio(void)
{
  float voltage = Get_Battery_Voltage();
  return (voltage - baseVoltage)*100/(8.4 - baseVoltage) ;
}
