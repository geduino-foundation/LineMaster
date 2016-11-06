#ifndef _BATTERY_H_
#define _BATTERY_H_

#include <Arduino.h>

class Battery {

  public:

    Battery(const uint8_t _battery_pin) :
      battery_pin(_battery_pin) {
      
      // Initialization
      init();
    
    };

    void readVoltage(float * volts);

    bool check(float * volts);

  private:

    const uint8_t battery_pin;

    void init();
  
};

#endif
