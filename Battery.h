#ifndef _BATTERY_H_
#define _BATTERY_H_

#include <Arduino.h>

class Battery {

  public:

    Battery(const unsigned int _battery_pin) :
      battery_pin(_battery_pin) {
      
      // Initialization
      init();
    
    };

    void readVoltage(float * volts);

    boolean check(float * volts);

  private:

    const unsigned int battery_pin;

    void init();
  
};

#endif
