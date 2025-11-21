#include <Arduino.h>

////////////////////Battery drive area/////////////////////////////////////
#define PIN_BATTERY        A6        //Set the battery detection voltage pin

// extern float batteryCoefficient;    //Set the proportional coefficient

int Get_Battery_Voltage_ADC(void);   //Gets the battery ADC value
float Get_Battery_Voltage(void);     //Get the battery voltage value 
int Get_Battery_ratio(void);
