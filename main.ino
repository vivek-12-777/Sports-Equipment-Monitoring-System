#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include "sensors.h"

// LCD (I2C address 0x27, 16x2)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Bluetooth (HC-05)
SoftwareSerial btSerial(10, 11); // RX, TX

void setup() {
  Serial.begin(9600);
  btSerial.begin(9600);

  // LCD initialization
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Initializing");

  // Initialize sensors (CALL)
  initSensors();

  lcd.clear();
  lcd.print("System Ready");
  delay(1000);
  lcd.clear();
}

void loop() {
  // Read sensor data (CALL)
  SensorData data = readSensors();

  // Display data on LCD
  lcd.setCursor(0, 0);
  lcd.print("Ax:");
  lcd.print(data.ax, 1);
  lcd.print(" Ay:");
  lcd.print(data.ay, 1);

  lcd.setCursor(0, 1);
  lcd.print("Gz:");
  lcd.print(data.gz, 1);
  lcd.print(" Az:");
  lcd.print(data.az, 1);

  // Send data via Bluetooth
  btSerial.println("---- Sensor Data ----");

  btSerial.print("MPU Accel (g): ");
  btSerial.print(data.ax); btSerial.print(", ");
  btSerial.print(data.ay); btSerial.print(", ");
  btSerial.println(data.az);

  btSerial.print("MPU Gyro (deg/s): ");
  btSerial.print(data.gx); btSerial.print(", ");
  btSerial.print(data.gy); btSerial.print(", ");
  btSerial.println(data.gz);

  btSerial.print("ADXL Accel (m/s^2): ");
  btSerial.print(data.adxl_x); btSerial.print(", ");
  btSerial.print(data.adxl_y); btSerial.print(", ");
  btSerial.println(data.adxl_z);

  btSerial.println();
  delay(500);
}

