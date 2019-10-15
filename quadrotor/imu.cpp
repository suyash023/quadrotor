#include "imu.h"

#include "Arduino.h"
#include <Wire.h>
#include <math.h>


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
  acc_x_raw = Wire.read()<<8 | Wire.read();
  acc_y_raw = Wire.read()<<8 | Wire.read();
  acc_z_raw = Wire.read()<<8 | Wire.read();
  int16_t temp = Wire.read()<<8 | Wire.read();
  gyro_x_raw = Wire.read()<<8 | Wire.read();
  gyro_y_raw = Wire.read()<<8 | Wire.read();
  gyro_z_raw = Wire.read()<<8 | Wire.read();
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




 /**
  * @brief method to display the computed values
  */

  void IMU::DisplayValues() {

    Serial.print("The Real value of accelerometer x-axis is: ");
    Serial.println(acc_x);
    Serial.print("The Real value of accelerometer y-axis is: ");
    Serial.println(acc_y);
    Serial.print("The Real value of accelerometer z-axis is: ");
    Serial.println(acc_z);
    Serial.print("The Real value of gyroscope x-axis is: ");
    Serial.println(gyro_x);
    Serial.print("The Real value of gyroscope y-axis is: ");
    Serial.println(gyro_y);
    Serial.print("The Real value of gyroscope x-axis is: ");
    Serial.println(gyro_x);
    Serial.print("The Roll angle by accelerometer is: ");
    Serial.println(roll_acc);
    Serial.print("The Pitch angle by accelerometer is: ");
    Serial.println(pitch_acc);
    Serial.print("The Yaw angle by accelerometer is : ");
    Serial.println(yaw_gyro);
    Serial.print("The pitch angle by gyroscope is : ");
    Serial.println(pitch_gyro);
    Serial.print("The roll angle by gyroscope is : ");
    Serial.println(roll_gyro);
    Serial.print("Loop frequency is: ");
    Serial.println(millis()-lastTime);
    delay(300); 
  }


  /**
   * @brief method to compute the roll, pitch and yaw values from accelerometer and gyroscope
   */
  void IMU::ComputeRPY() {
    roll_acc = 180*atan2(acc_y,sqrt(acc_x * acc_x + acc_z * acc_z)) / 3.14;
    pitch_acc = 180*atan2(acc_z,sqrt(acc_x * acc_x + acc_y * acc_y)) / 3.14;
    yaw_gyro = yaw_gyro + gyro_x * ((millis() - lastTime)/1000);
    roll_gyro = roll_gyro + gyro_z* ((millis() - lastTime)/1000);
    pitch_gyro = pitch_gyro + gyro_y *((millis() - lastTime)/1000); 
    
  }
