#include "imu.h"
#include "motor.h"
#include "PIDController.h"
#include "complimentaryFilter.h"

IMU mpu6050;
void setup() {
  // put your setup code here, to run once:
  mpu6050.Setup();
  mpu6050.ReadRawValues();
  mpu6050.ConvertToReal();
}

void loop() {
  // put your main code here, to run repeatedly:

}
