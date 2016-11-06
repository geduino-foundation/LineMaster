#ifndef _PID_H_
#define _PID_H_

#include <Arduino.h>

#include "types.h"

class PID {

  public:

    PID() {
      
      // Initialization
      this->init();
    
    };

    void setup(const Setup & setup);
    
    void update(const int & error, int * correction);
    
  private:

    float proportional;
    float integrative;
    float derivative;
    
    int last_error;
    long integral;
    
    void init();

    void reset();
  
};

#endif
