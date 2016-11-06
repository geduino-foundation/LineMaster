#ifndef _TELEMETRY_H_
#define _TELEMETRY_H_

#include <Arduino.h>

#include "types.h"

class Telemetry {

  public:

    const uint16_t size;

    TelemetryData * data;

    Telemetry(const uint16_t _size) :
      size(_size) {
      
      // Initialization
      this->init();
    
    };

    void reset();

    bool add(const uint32_t & time, const int16_t & error);
    
  private:

    uint16_t index;
    
    void init();
  
};

#endif
