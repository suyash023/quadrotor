#include "motor.h"


#include "Arduino.h"

void Motor::setMotorSpeed(int speedVoltLevel) {
  if (speedVoltLevel <= 255 && speedVoltLevel >= 0) {
    analogWrite(motorPin, speedVoltLevel); 
    delay(50);
    motorSpeed = speedVoltLevel;
  } else {
    analogWrite(motorPin, motorSpeed);
    delay(50);
  }
}

void Motor::setMotorPin(unsigned int pin) {
  pinMode( pin, OUTPUT);
  motorPin = pin;
}
