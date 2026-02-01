#include "sensors.h"
#include <Wire.h>

// Sensor objects
MPU6050 mpu;
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

void initSensors() {
  Wire.begin();

  // Initialize MPU6050
  mpu.initialize();

  // Initialize ADXL345
  accel.begin();
}

SensorData readSensors() {
  SensorData data;

  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  sensors_event_t event;
  accel.getEvent(&event);

  // Convert raw MPU6050 values
  data.ax = ax / 16384.0;
  data.ay = ay / 16384.0;
  data.az = az / 16384.0;

  data.gx = gx / 131.0;
  data.gy = gy / 131.0;
  data.gz = gz / 131.0;

  // ADXL345 values
  data.adxl_x = event.acceleration.x;
  data.adxl_y = event.acceleration.y;
  data.adxl_z = event.acceleration.z;

  return data;
}
