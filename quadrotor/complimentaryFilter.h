#ifndef complimentaryFilter_h
#define complimentaryFilter_h

#include "Arduino.h"

/**
 * @class complimentaryFilter complimentaryFilter.h
 * @brief class that implements complimentary filter based on a set weight
 */


 class ComplimentaryFilter {
  private:
    float weightRoll = 0;
    float weightPitch = 0;
    float weightYaw = 0;
    
  public:
    bool SetRollWeight(float weight);
    bool SetPitchWeight(float weight);
    bool SetYawWeight(float weight);
    float FilterImplementation(float reading1, float reading2);
 };

 #endif
