#ifndef _PID_H_
#define _PID_H_

#include <Arduino.h>

#include "SerialSetup.h"

class PID {

  public:

    PID() {
      
      // Initialization
      this->init();
    
    };

    void setup(Settings settings);
    
    void update(int error, int * correction);
    
  private:

    float proportional;
    float integrative;
    float derivative;
    int motorsMaxSpeed;
    
    int lastError;
    long integral;
    
    void init();

    void reset();
  
};

#endif
