#include "imu.h"
#include "motor.h"
#include "PIDController.h"
#include "complimentaryFilter.h"

IMU mpu6050;
ComplimentaryFilter cf;
void setup() {
  // put your setup code here, to run once:
  mpu6050.Setup();
  mpu6050.GyroCorrection();
  mpu6050.AccCorrection();
  Serial.begin(38400);
  cf.SetRollWeight(0.9);
  cf.SetPitchWeight(0.9);
}

void loop() {
  // put your main code here, to run repeatedly:
  mpu6050.lastTime = millis();
  mpu6050.ReadRawValues();
  mpu6050.ConvertToReal();
  mpu6050.GyroCorrection();
  mpu6050.ComputeRPacc();
  mpu6050.ComputeRPYgyro();
  mpu6050.AccCorrection();
  float rollReading = cf.FilterRollImplementation(  mpu6050.roll_acc, mpu6050.roll_gyro);
  float pitchReading = cf.FilterPitchImplementation( mpu6050.pitch_acc, mpu6050.pitch_gyro);
  cf.DisplayValues(rollReading, pitchReading, 0);
   
  //mpu6050.DisplayValues();
}
