#include "imu.h"
#include "motor.h"
#include "PIDController.h"
#include "complimentaryFilter.h"

IMU mpu6050;
void setup() {
  // put your setup code here, to run once:
  mpu6050.Setup();
  Serial.begin(38400);
}

void loop() {
  // put your main code here, to run repeatedly:
  float loopTime = millis();
  mpu6050.lastTime = loopTime;
  mpu6050.ReadRawValues();
  mpu6050.ConvertToReal();
  mpu6050.ComputeRPY();
  mpu6050.DisplayValues();

}
