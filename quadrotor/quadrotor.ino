#include "imu.h"
#include "motor.h"
#include "PIDController.h"
#include "complimentaryFilter.h"

IMU mpu6050;
ComplimentaryFilter cf;
PIDController pitchControl, rollControl, yawControl;
Motor motor1, motor2, motor3, motor4;
void setup() {
  // put your setup code here, to run once:
  mpu6050.Setup();
  mpu6050.GyroCorrection();
  mpu6050.AccCorrection();
  Serial.begin(38400);
  cf.SetRollWeight(0.9);
  cf.SetPitchWeight(0.9);
  rollControl.SetPIDValues(1, 0, 0);
  pitchControl.SetPIDValues(1, 0, 0);
  yawControl.SetPIDValues(1, 0, 0);
  motor1.setMotorPin(3);
  motor2.setMotorPin(4);
  motor3.setMotorPin(10);
  motor4.setMotorPin(11);


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
  float rollCorrection = rollControl.RunPID( rollReading, 0);
  float pitchCorrection = pitchControl.RunPID( pitchReading, 0);
  float yawCorrection = yawControl.RunPID( mpu6050.gyro_x, 0);
  cf.DisplayValues(rollReading, pitchReading, 0);
  Serial.print("Roll correction is: ");
  Serial.println(rollCorrection);
  Serial.print("Pitch correction is: ");
  Serial.println(pitchCorrection);
  Serial.print("Yaw correction is: ");
  Serial.println(yawCorrection);
  delay(10); 
}
