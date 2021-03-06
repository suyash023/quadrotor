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
float rollReading = 0.0;
float pitchReading = 0.0;
void setup() {
  // put your setup code here, to run once:
  mpu6050.Setup();
  mpu6050.GyroCorrection();
  mpu6050.AccCorrection();
  Serial.begin(38400);
  cf.SetRollWeight(0.7);
  cf.SetPitchWeight(0.7);
  rollControl.SetPIDValues(0.1, 0.05, 0.2);
  pitchControl.SetPIDValues(0.1, 0.05, 0.2);
  yawControl.SetPIDValues(10, 0, 0);
  
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

  rollReading = cf.FilterRollImplementation(  rollReading, mpu6050.roll_acc, mpu6050.roll_gyro);
  pitchReading = cf.FilterPitchImplementation( pitchReading, mpu6050.pitch_acc, mpu6050.pitch_gyro);
  int rollCorrection = (int)(rollControl.RunPID( rollReading, 0, mpu6050.gyro_z)/2);
  int pitchCorrection = (int)(pitchControl.RunPID( pitchReading, 0, mpu6050.gyro_y)/2);
  int yawCorrection = (int)(yawControl.RunPID( mpu6050.gyro_x, 0, 0)/2);
  //cf.DisplayValues(rollReading, pitchReading, 0);
  if (quadSpeed > 0 ) {
//    motor1.setMotorSpeed((quadSpeed + rollCorrection));
//    motor4.setMotorSpeed((quadSpeed + rollCorrection));
//    motor2.setMotorSpeed((quadSpeed - rollCorrection));
//    motor3.setMotorSpeed((quadSpeed - rollCorrection));
//    delay(10);
//
//    motor1.setMotorSpeed((quadSpeed - pitchCorrection));
//    motor2.setMotorSpeed((quadSpeed - pitchCorrection));
//    motor3.setMotorSpeed((quadSpeed + pitchCorrection));
//    motor4.setMotorSpeed((quadSpeed + pitchCorrection));
//    delay(10);
//    motor1.setMotorSpeed(quadSpeed + yawCorrection);
//    motor3.setMotorSpeed(quadSpeed + yawCorrection);
//    motor4.setMotorSpeed(quadSpeed - yawCorrection);
//    motor2.setMotorSpeed(quadSpeed - yawCorrection);
//    delay(10);
      motor1.setMotorSpeed((quadSpeed + rollCorrection - pitchCorrection + yawCorrection));
      motor4.setMotorSpeed((quadSpeed + rollCorrection + pitchCorrection - yawCorrection));
      motor2.setMotorSpeed((quadSpeed - rollCorrection - pitchCorrection - yawCorrection));
      motor3.setMotorSpeed((quadSpeed - rollCorrection + pitchCorrection + yawCorrection));
      //delay(5);
  }
  if(Serial.available()) {
    char command;
    command = Serial.read();
    if(command == 'w') {
      Serial.print("quad speed: ");
      if ( quadSpeed < 255) {
        quadSpeed = quadSpeed + incrementalSpeed;
//        motor1.setMotorSpeed(quadSpeed);
//        motor2.setMotorSpeed(quadSpeed);
//        motor3.setMotorSpeed(quadSpeed);
//        motor4.setMotorSpeed(quadSpeed);
      } else {
        Serial.println("Already at full speed");
      }
      Serial.println(quadSpeed);
    } else if (command == 'x') {
      Serial.print("quad speed: ");
      if (quadSpeed > incrementalSpeed ) {
        quadSpeed = quadSpeed - incrementalSpeed;
//        motor1.setMotorSpeed(quadSpeed);
//        motor2.setMotorSpeed(quadSpeed);
//        motor3.setMotorSpeed(quadSpeed);
//        motor4.setMotorSpeed(quadSpeed);
        
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
      rollControl.ResetErrors();
      pitchControl.ResetErrors();
      yawControl.ResetErrors();
      quadSpeed = 0;
    } else if (command == 'd') {
      cf.DisplayValues(rollReading, pitchReading, 0);
      //mpu6050.DisplayValues();
    }
  }
  //cf.PlotValues(rollReading, pitchReading, 0);
//  Serial.print("Motor 1 speed: ");
//  Serial.println(motor1.motorSpeed);
//  Serial.print("Motor 2 speed: ");
//  Serial.println(motor2.motorSpeed);
//  Serial.print("Motor 3 speed: ");
//  Serial.println(motor3.motorSpeed);
//  Serial.print("Motor 4 speed: ");
//  Serial.println(motor4.motorSpeed);
  //delay(10); 
}
