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
  int16_t acc_sentitivity = 16384;
  int gyro_sensitvity = 131;
  float acc_x = 0;
  float acc_y = 0;
  float acc_z = 0;
  float gyro_x = 0;
  float gyro_y = 0;
  float gyro_z = 0;
  float roll = 0;
  float pitch = 0;
  float yaw = 0;
 private:
  int mpu_addr = 0x68;

  public:
    
    void Setup();

    void ReadRawValues();

    void ConvertToReal();

    void ComputeRPY();

    void DisplayValues();




};

#endif
