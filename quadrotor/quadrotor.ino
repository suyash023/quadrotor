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
  motor1.setMotorPin(11);
  motor2.setMotorPin(3);
  motor3.setMotorPin(6);
  motor4.setMotorPin(10);
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
  unsigned char rollCorrection = (unsigned char)(rollControl.RunPID( rollReading, 0)/2);
  unsigned char pitchCorrection = (unsigned char)(pitchControl.RunPID( pitchReading, 0)/2);
  unsigned char yawCorrection = (unsigned char)(yawControl.RunPID( mpu6050.gyro_x, 0)/2);
  cf.DisplayValues(rollReading, pitchReading, 0);
  motor1.setMotorSpeed((motor1.motorSpeed + rollCorrection));
  motor4.setMotorSpeed((motor4.motorSpeed + rollCorrection));
  motor2.setMotorSpeed((motor2.motorSpeed - rollCorrection));
  motor3.setMotorSpeed((motor3.motorSpeed - rollCorrection));
  Serial.print("Motor 1 speed: ");
  Serial.println(motor1.motorSpeed);
  Serial.print("Motor 2 speed: ");
  Serial.println(motor2.motorSpeed);
  Serial.print("Motor 3 speed: ");
  Serial.println(motor3.motorSpeed);
  Serial.print("Motor 4 speed: ");
  Serial.println(motor4.motorSpeed);
  delay(10); 
}
