#ifndef _TELEMETRY_H_
#define _TELEMETRY_H_

#include <Arduino.h>

#include "types.h"

class Telemetry {

  public:

    const unsigned int size;

    TelemetryData * data;

    Telemetry(const unsigned int _size) :
      size(_size) {
      
      // Initialization
      this->init();
    
    };

    void reset();

    bool add(const unsigned long & time, const int & error);
    
  private:

    unsigned int index;
    
    void init();
  
};

#endif
