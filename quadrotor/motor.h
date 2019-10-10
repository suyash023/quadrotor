#ifndef motor_h
#define motor_h


#include "Arduino.h"

/**
 * @class Motor motor.h
 * @brief Class defining a motor and functions to set and get motor speeds
 *
 */

class Motor {
 public:
    unsigned int motorSpeed = 0;
 private:
    unsigned int motorPin = -1;
 public:
    void setMotorSpeed(int speedVoltLevel);
    unsigned int getMotorSpeed();
    void setMotorPin(unsigned int pin);
};

#endif
