#ifndef _MOTORS_H_
#define _MOTORS_H_

#include <Arduino.h>

class Motors {

  public:

    Motors(const int _motorSxPin, const int _motorDxPin) :
      motorSxPin(_motorSxPin), motorDxPin(_motorDxPin) {
      
      // Initialization
      this->init();
    
    };

    void setMotorPwmFrequency();

    void setSpeed(const int sx, const int dx);

    void stop();

  private:

    const unsigned int motorSxPin, motorDxPin;

    void init();
  
};

#endif
