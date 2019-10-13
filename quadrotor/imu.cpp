#include "imu.h"

#include "Arduino.h"
#include <Wire.h>


/**
 * @brief method to wake up imu and start it. Uses i2c communication (Wire library in arduino)
 * Sets power managmenet to basic mode, and wakes up the imu
 */

 void IMU::Setup() {
  Wire.begin();
  Wire.beginTransmission(this->mpu_addr);
  Wire.write(0x6b); //set power management to 1.
  Wire.write(0); //wake up MPU 6050
  Wire.endTransmission(true);
 }

/**
 * @brief Method to read the raw values from accelerometer and gyroscope.
 */
void IMU::ReadRawValues() {
  Wire.beginTransmission(this->mpu_addr);
  Wire.write(0x3b);
  Wire.endTransmission(false);
  Wire.requestFrom(this->mpu_addr,14,true);
  this->acc_x_raw = Wire.read()<<8 | Wire.read();
  this->acc_y_raw = Wire.read()<<8 | Wire.read();
  this->acc_z_raw = Wire.read()<<8 | Wire.read();
  int16_t temp = Wire.read()<<8 | Wire.read();
  this->gyro_x_raw = Wire.read()<<8 | Wire.read();
  this->gyro_y_raw = Wire.read()<<8 | Wire.read();
  this->gyro_z_raw = Wire.read()<<8 | Wire.read();
}


/**
 * @brief Method to convert the raw value of accelerometer and gyroscope
 * to real values in g's and radians/sec
 */
void IMU::ConvertToReal() {
  this->acc_x = (float)this->acc_x_raw/this->acc_sensitivity;
  this->acc_y = (float)this->acc_y_raw/this->acc_sensitivity;
  this->acc_z = (float)this->acc_z_raw/this->acc_sensitivity;
  this->gyro_x = (float)this->gyro_x_raw/this->gyro_sensitivity;
  this->gyro_y = (float)this->gyro_y_raw/this->gyro_sensitivity;
  this->gyro_z = (float)this->gyro_z_raw/this->gyro_sensitivity;
}
