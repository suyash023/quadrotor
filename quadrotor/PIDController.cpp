#include "PIDController.h"

#include "Arduino.h"

/**
 * @brief Function to set the PID values of the controller
 * @param kpIn kiIn kdIn kp, ki and kd values to be set
 * @return bool specifying if the values vould be set or not
 */

bool PIDController::SetPIDValues(float kpIn, float kiIn, float kdIn) {
  if( kpIn > 0 && kiIn >= 0 && kdIn >= 0) {
    kp = kpIn;
    ki = kiIn;
    kd = kdIn;
    return true;
  } else {
    return false;
  }
}

/**
 * @brief Function to run the pid controller and find the correction values for motors
 * @param currentValue targetValue currentValue (sensor reading) targetValue (angle to be maintained)
 * @return float correction value to be applied on motor speeds.
 */


float PIDController::RunPID(float currentValue, float targetValue) {
  float error = 0;
  float errorDiff = 0;
  float correction;
  error = currentValue - targetValue;
  //Serial.print("Error is: ");
  //Serial.println(error);
  errorSum = errorSum + error;
  errorDiff = error - lastError;
  correction = kp* ( error ) + ki * ( errorSum ) + kd * (errorDiff);
  lastError = error;
  return correction;
}

/**
 * @brief Function to reset the error sum and last error to 0
 * @param none
 * @return non
 */
void PIDController::ResetErrors() {
  errorSum = 0;
  lastError = 0;
}
