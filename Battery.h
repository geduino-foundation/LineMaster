#ifndef _BATTERY_H_
#define _BATTERY_H_

#include <Arduino.h>

class Battery {

  public:

    Battery(const unsigned int _batteryPin) : batteryPin(_batteryPin) {
      
      // Initialization
      init();
    
    };

    void readVoltage(float * volts);

    boolean check(float * volts);

  private:

    const unsigned int batteryPin;

    void init();
  
};

#endif
