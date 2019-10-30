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
    unsigned char motorSpeed = 0;
 private:
    unsigned char motorPin = 0;
 public:
    void setMotorSpeed(int speedVoltLevel);
    void setMotorPin(unsigned int pin);
};

#endif
