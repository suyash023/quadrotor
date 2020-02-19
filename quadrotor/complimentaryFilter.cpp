#include "complimentaryFilter.h"


#include "Arduino.h"

/**
 * @brief Function to set the complmentary filter weight values between 0 and 1 for Roll angle
 * @param value Value to be set
 * @return boolean variable specifying if the value was set
 */

bool ComplimentaryFilter::SetRollWeight(float value) {
  if(value >= 0 && value < 1) {
    weightRoll = value;
    return true;
  } else {
    return false;
  }
}

/**
 * @brief Function to set the complimentary filter weight values between 0 and 1 for Pitch angle
 * @param value Value of weight to be set
 * @return boolean variable specifying if the value was set
 */
bool ComplimentaryFilter::SetPitchWeight(float value) {
  if(value >= 0 && value < 1) {
    weightPitch = value;
    return true;
  } else {
    return false;
  }
}

/**
 * @brief Function to set the Complimentary folter weight values for Yaw angle (not done for accelerometer and gyroscope
 * as acclerometer does not give yaw values 
 * @param value Value of weight to be set
 * @return boolean variable specifying if the value was set
 */
bool ComplimentaryFilter::SetYawWeight(float value) {
  if( value >= 0 && value < 1) {
    weightYaw = value;
    return true;
  } else {
    return false;
  }
}

/**
 * @brief Function to implement the complimentary filter for roll
 * @param reading1 Reading from either accelerometer or gyroscope
 * @param reading2 Reading from either accelerometer or gyroscope
 * @return the filtered value
 */

float ComplimentaryFilter::FilterRollImplementation(float prevReading, float reading1, float reading2) {
  float filteredValue;
  filteredValue = (weightRoll * reading1) + ((1 - weightRoll) * (prevReading + reading2));
  return filteredValue;
 }

 /**
  * @brief Function to implement the complimentary filter for pitch
  * @param reading1 Reading from either accelerometer or Gyroscope
  * @param reading2 Reading from either accelerometer or gyroscope
  * @return the filtered value 
  */
 float ComplimentaryFilter::FilterPitchImplementation(float prevReading, float reading1, float reading2) {
    float filteredValue;
    filteredValue = (weightPitch * reading1) + ((1 - weightPitch) * (prevReading + reading2));
    return filteredValue;
  }

  /**
   * @brief Function to implement the complimentary filter for yaw (accelerometer does not give yaw values)
   * (magenetometer is needed)
   * @param reading1 Reading from either accelerometer or gyroscope
   * @param reading2 Reading from either accelerometer or gyroscope
   * @return the filtered value
   */
 float ComplimentaryFilter::FilterYawImplementation(float prevReading, float reading1, float reading2) {
    float filteredValue;
    filteredValue = (weightYaw * reading1) + ((1 - weightYaw) * (prevReading + reading2));
    return filteredValue;
   }

   /**
    * @brief Function to display filtered values
    * @param reading_acc reading from accelerometer
    * @param reading_gryo reading from gyroscope
    * @return none
    */
  void ComplimentaryFilter::DisplayValues(float readingRoll, float readingPitch, float readingYaw) {
      Serial.print("The filtered roll value is: ");
      Serial.println(readingRoll);
      Serial.print("The filtered pitch value is: ");
      Serial.println(readingPitch);
      Serial.print("The filtered yaw value is: ");
      Serial.println(readingYaw);
      delay(10);
    }
