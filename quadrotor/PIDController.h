#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H

#include "Arduino.h"

/**
 * @class PIDController PIDController.h
 * @brief Class for PID controller. Can set PID values
 * and perform control of separate dimension. Can also execute PID
 */

 class PIDController {
  private:
      float kp = 0;
      float ki = 0;
      float kd = 0;
      float currentError = 0;
      float lastError = 0;
      float errorSum = 0;

  public:
      bool SetPIDValues(float kp, float ki, float kd);
      float ReturnKpValue();
      float ReturnKiValue();
      float ReturnKdValue();
      void updateErrorSum();
      float updateLastError();
 };


#endif
