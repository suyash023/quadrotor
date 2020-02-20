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
  Wire.beginTransmission(this->mpu_addr);
  Wire.write(0x1A);                    // write to address 26 of the register
  Wire.write(0x06);                    // options here are 0x00 which is off, and 0x01, 0x02, 0x03, 0x04, 0x05, 0x06
  Wire.endTransmission(true);
  delay(100);
 }

/**
 * @brief Method to read the raw values from accelerometer and gyroscope.
 */
void IMU::ReadRawValues() {
  Wire.beginTransmission(mpu_addr);
  Wire.write(0x3b);
  Wire.endTransmission(false);
  Wire.requestFrom(mpu_addr,14,true);
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
  acc_x = (float)acc_x_raw/acc_sensitivity;
  acc_y = (float)acc_y_raw/acc_sensitivity;
  acc_z = (float)acc_z_raw/acc_sensitivity;
  gyro_x = (float)gyro_x_raw/gyro_sensitivity;
  gyro_y = (float)gyro_y_raw/gyro_sensitivity;
  gyro_z = (float)gyro_z_raw/gyro_sensitivity;
}




 /**
  * @brief method to display the computed values
  */

  void IMU::DisplayValues() {

//    Serial.print("The Real value of accelerometer x-axis is: ");
//    Serial.println(acc_x);
//    Serial.print("The Real value of accelerometer y-axis is: ");
//    Serial.println(acc_y);
//    Serial.print("The Real value of accelerometer z-axis is: ");
//    Serial.println(acc_z);
//    Serial.print("The Real value of gyroscope x-axis is: ");
//    Serial.println(gyro_x);
//    Serial.print("The Real value of gyroscope y-axis is: ");
//    Serial.println(gyro_y);
//    Serial.print("The Real value of gyroscope z-axis is: ");
//    Serial.println(gyro_z);
    Serial.print("The Roll angle by accelerometer is: ");
    Serial.println(roll_acc);
    Serial.print("The Pitch angle by accelerometer is: ");
    Serial.println(pitch_acc);
    Serial.print("The Yaw angle by gyroscope is : ");
    Serial.println(gyro_x);
    Serial.print("The pitch angle by gyroscope is : ");
    Serial.println(pitch_gyro);
    Serial.print("The roll angle by gyroscope is : ");
    Serial.println(roll_gyro);
//    Serial.print("The gyroscope x correction is : ");
//    Serial.println(corr_gyro_x);
//    Serial.print("The gyroscope y correction is : ");
//    Serial.println(corr_gyro_y);
//    Serial.print("The gyroscope z correction is : ");
//    Serial.println(corr_gyro_z);
//    Serial.print("The accelerometer pitch correction is : ");
//    Serial.println(corr_acc_roll);
//    Serial.print("The accelerometer roll correction is : ");
//    Serial.println(corr_acc_pitch);
    Serial.print("Loop frequency is: ");
    Serial.println(millis()-lastTime);
    delay(10); 
  }


  /**
   * @brief method to compute the roll, pitch  from accelerometer
   */
  void IMU::ComputeRPacc() {
    roll_acc = 180*atan2(acc_y,sqrt(acc_x * acc_x + acc_z * acc_z)) / 3.14;
    pitch_acc = 180*atan2(acc_z,sqrt(acc_x * acc_x + acc_y * acc_y)) / 3.14; 
  }

/**
 * @brief method to compute the roll, pitch and yaw from gyroscopes 
 */
 void IMU::ComputeRPYgyro() {
    yaw_gyro =   180*(gyro_x * ((millis() - lastTime)/1000))/3.14;
    roll_gyro =   180*(gyro_z* ((millis() - lastTime)/1000))/3.14;
    pitch_gyro = 180*(gyro_y *((millis() - lastTime)/1000))/3.14;
 }

 /**
 * @brief Method for correction of gyroscope values, when quadrotor is completely still (first 100 readings)
 */

 void IMU::GyroCorrection() {
  if( gyro_corrected == false) {
    for(int i = 0 ;i < 100; i++) {
      ReadRawValues();
      ConvertToReal();
      corr_gyro_x = corr_gyro_x + gyro_x;
      corr_gyro_y = corr_gyro_y + gyro_y;
      corr_gyro_z = corr_gyro_z + gyro_z;
    }
    corr_gyro_x = corr_gyro_x/100;
    corr_gyro_y = corr_gyro_y/100;
    corr_gyro_z = corr_gyro_z/100;
    gyro_corrected = true;
  } else {
    gyro_x = gyro_x - corr_gyro_x;
    gyro_y = gyro_y - corr_gyro_y;
    gyro_z = gyro_z - corr_gyro_z;
  }
}

/**
 * @brief Method to correct for the accelerometer reading
 */

 void IMU::AccCorrection() {
  if ( acc_corrected == false) {
    for(int i = 0; i< 100; i++) {
      ReadRawValues();
      ConvertToReal();
      ComputeRPacc();
      corr_acc_roll = corr_acc_roll + roll_acc;
      corr_acc_pitch = corr_acc_pitch + pitch_acc;
    }
    corr_acc_roll = corr_acc_roll / 100;
    corr_acc_pitch = corr_acc_pitch /100;
    acc_corrected = true;
  } else {
    roll_acc = corr_acc_roll - roll_acc;
    pitch_acc = pitch_acc - corr_acc_pitch;
  }
 }
