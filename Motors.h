#ifndef _MOTORS_H_
#define _MOTORS_H_

#include <Arduino.h>

#include "settings.h"

class Motors {

  public:

    Motors(const int _motorSxPin, const int _motorDxPin) :
      motorSxPin(_motorSxPin), motorDxPin(_motorDxPin) {
      
      // Initialization
      this->init();
    
    };

    void setMotorPwmFrequency();

    void setup(Settings settings);
    
    void setSpeed(const int correction);

    void stop();

  private:

    const unsigned int motorSxPin, motorDxPin;

    unsigned int maxSpeed;

    void init();
  
};

#endif
