#ifndef _MOTORS_H_
#define _MOTORS_H_

#include <Arduino.h>

#include "types.h"

class Motors {

  public:

    Motors(const int _motor_sx_pin, const int _motor_dx_pin) :
      motor_sx_pin(_motor_sx_pin), motor_dx_pin(_motor_dx_pin) {
      
      // Initialization
      this->init();
    
    };

    void setMotorPwmFrequency();

    void setup(const Setup & setup);
    
    void setSpeed(const int & correction);

    void stop();

  private:

    const unsigned int motor_sx_pin, motor_dx_pin;

    unsigned int max_speed;

    void init();
  
};

#endif
