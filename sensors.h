#ifndef SENSORS_H
#define SENSORS_H

#include <MPU6050.h>
#include <Adafruit_ADXL345_U.h>
#include <Adafruit_Sensor.h>

// Structure to store all sensor outputs
struct SensorData {
  float ax, ay, az;
  float gx, gy, gz;
  float adxl_x, adxl_y, adxl_z;
};

// Function declarations
void initSensors();
SensorData readSensors();

#endif
