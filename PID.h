#ifndef _PID_H_
#define _PID_H_

#ifdef ARDUINO
#include <Arduino.h>
#endif

#include "types.h"

#ifndef ARDUINO
#define NULL __null
#define constrain(v, a, b) ((v < a) ? a : (v > b) ? b : v)
#endif

class PID {

  public:

    PID() {
      
      // Initialization
      this->init();
    
    }
    
    void setup(const Setup & setup);
    
    void update(const int16_t & error, int16_t * correction);
    
  private:

    float proportional;
    float integrative;
    float derivative;
    int16_t pid_max_proportional;
    int16_t pid_max_integrative;
    int16_t pid_max_derivative; 
    int16_t pid_max_correction;
    
    int16_t last_error;
    int32_t integral;
    
    void init();

    void reset();
  
};

#endif
