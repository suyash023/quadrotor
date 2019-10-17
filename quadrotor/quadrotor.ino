#include "imu.h"
#include "motor.h"
#include "PIDController.h"
#include "complimentaryFilter.h"

IMU mpu6050;
void setup() {
  // put your setup code here, to run once:
  mpu6050.Setup();
  mpu6050.GyroCorrection();
  mpu6050.AccCorrection();
  Serial.begin(38400);
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
  //mpu6050.DisplayValues();
}
