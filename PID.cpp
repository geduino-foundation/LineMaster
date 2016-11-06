#include "PID.h"

void PID::setup(const Setup & setup) {

  proportional = setup.pid_proportional / 10000.0;
  integrative = setup.pid_integrative / 10000.0;
  derivative = setup.pid_derivative / 10000.0;

  // Reset
  reset();
  
}

void PID::update(const int16_t & error, int16_t * correction) {

  int32_t derivate = 0;

  if (last_error != NULL) {

    // Calculate derivate
    derivate = error - last_error;
    
  } else {

    // Set derivate to zero
    derivate = 0;
    
  }

  // Calculate integral
  integral += error;

  // Calculate correction
  * correction = error * proportional + derivate * derivative + integral * integrative;
  
  // Set last error for next iteration
  last_error = error;
  
}

void PID::init() {

  // Reset
  reset();
  
}

void PID::reset() {

  // Init last error to NULL
  last_error = NULL;

  // Init integral to zero
  integral = 0;
  
}
