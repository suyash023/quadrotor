#ifndef imu_h
#define imu_h

#include "Arduino.h"
/**
  @class IMU imu.h
  @brief Class for IMU Object. Gets raw values from i2c from mpu 6050.
  Computes the actual accelerometer values in g m/s^2
  Computes the actual gyroscope values in rad/s
*/

class IMU {
 public:
  int16_t acc_x_raw = 0;
  int16_t acc_y_raw = 0;
  int16_t acc_z_raw = 0;
  int16_t gyro_x_raw = 0;
  int16_t gyro_y_raw = 0;
  int16_t gyro_z_raw = 0;
  int16_t acc_sensitivity = 16384;
  int gyro_sensitivity = 131;
  float acc_x = 0;
  float acc_y = 0;
  float acc_z = 0;
  float gyro_x = 0;
  float gyro_y = 0;
  float gyro_z = 0;
  float roll_acc = 0;
  float pitch_acc = 0;
  float roll_gyro = 0;
  float pitch_gyro = 0; 
  float yaw_gyro = 0;
  float lastTime = 0;
  bool gyro_corrected = false;
  bool acc_corrected = false;
  float corr_gyro_x = 0;
  float corr_gyro_y = 0;
  float corr_gyro_z = 0;
 private:
  int mpu_addr = 0x68;

  public:
    
    void Setup();

    void ReadRawValues();

    void ConvertToReal();

    void ComputeRPY();

    void DisplayValues();

    void GyroCorrection();

    void AccelerometerCorrection();



};

#endif
