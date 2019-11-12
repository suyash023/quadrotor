#include "imu.h"
#include "motor.h"
#include "PIDController.h"
#include "complimentaryFilter.h"

IMU mpu6050;
ComplimentaryFilter cf;
PIDController pitchControl, rollControl, yawControl;
Motor motor1, motor2, motor3, motor4;
int quadSpeed = 0;
int incrementalSpeed = 10;
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
  //motor1.StartUp(200);
  //motor2.StartUp(200);
  //motor3.StartUp(200);
  //motor4.StartUp(200);
  //quadSpeed = 200;
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()) {
    char command;
    command = Serial.read();
    if(command == 'w') {
      Serial.print("quad speed: ");
      if ( quadSpeed < 255) {
        quadSpeed = quadSpeed + incrementalSpeed;
        motor1.setMotorSpeed(quadSpeed);
        motor2.setMotorSpeed(quadSpeed);
        motor3.setMotorSpeed(quadSpeed);
        motor4.setMotorSpeed(quadSpeed);
      } else {
        Serial.println("Already at full speed");
      }
      Serial.println(quadSpeed);
    } else if (command == 'x') {
      Serial.print("quad speed: ");
      if (quadSpeed > incrementalSpeed ) {
        quadSpeed = quadSpeed - incrementalSpeed;
        motor1.setMotorSpeed(quadSpeed);
        motor2.setMotorSpeed(quadSpeed);
        motor3.setMotorSpeed(quadSpeed);
        motor4.setMotorSpeed(quadSpeed);
        
      } else {
        Serial.println("Already at low speed");
      }
      Serial.println(quadSpeed);
    } else if (command == 'k') {
      Serial.println("Kill Switch hit!");
      motor1.setMotorSpeed(0);
      motor2.setMotorSpeed(0);
      motor3.setMotorSpeed(0);
      motor4.setMotorSpeed(0);
      quadSpeed = 0;
    }
  }
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
  //cf.DisplayValues(rollReading, pitchReading, 0);
  if (quadSpeed > 0 ) {
    motor1.setMotorSpeed((quadSpeed + rollCorrection));
    motor4.setMotorSpeed((quadSpeed + rollCorrection));
    motor2.setMotorSpeed((quadSpeed - rollCorrection));
    motor3.setMotorSpeed((quadSpeed - rollCorrection));
  }
  //Serial.print("Motor 1 speed: ");
  //Serial.println(motor1.motorSpeed);
  //Serial.print("Motor 2 speed: ");
  //Serial.println(motor2.motorSpeed);
  //Serial.print("Motor 3 speed: ");
  //Serial.println(motor3.motorSpeed);
  //Serial.print("Motor 4 speed: ");
  //Serial.println(motor4.motorSpeed);
  //delay(10); 
}
