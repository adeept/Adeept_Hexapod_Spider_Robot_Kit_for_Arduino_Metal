#ifndef __MPU6050_H__
#define __MPU6050_H__
#include <Arduino.h>
#include <Wire.h>
#define MPU6050_I2C_ADDR 0x68 // I2C address of the MPU-6050

void Mpu6050_Setup();
void getMotion6();
void count6Axle();
void getOffsetAngle(float& offset_x, float& offset_y, float& offset_z);

#endif
