#include "motor.h"


#include "Arduino.h"

void Motor::setMotorSpeed(int speedVoltLevel, int timeDelay) {
  analogWrite(motorPin, speedVoltLevel);
  delay(timeDelay);
}

void Motor::setMotorPin(unsigned int pin) {
  pinMode( pin, OUTPUT);
}
