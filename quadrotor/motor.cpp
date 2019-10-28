#include "motor.h"


#include "Arduino.h"

Motor::setMotorSpeed(int speedVoltLevel, int timeDelay) {
  analogWrite(motorPin, speedVoltLevel);
  delay(timeDelay);
}

Motor::setMotorPin(unsigned int pin) {
  pinMode( pin, OUTPUT);
}
