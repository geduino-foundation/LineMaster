#ifndef _PID_H_
#define _PID_H_

#include <Arduino.h>

struct PidSetup {
    float proportional;
    float integrative;
    float derivative;
    int motorMaxSpeed;
};

class PID {

  public:

    PID(const PidSetup * _pidSetup) : pidSetup(_pidSetup) {
      
      // Initialization
      this->init();
    
    };

    void update(int error, int * correction);
    
  private:

    const PidSetup * pidSetup;

    void init();

    int lastError;
    long integral;
  
};

#endif
