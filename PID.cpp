#include "PID.h"

void PID::update(int error, int * correction) {

  long derivate = 0;

  if (lastError != NULL) {

    // Calculate derivate
    derivate = error - lastError;
    
  } else {

    // Set derivate to zero
    derivate = 0;
    
  }

  // Calculate integral
  integral += error;

  // Calculate correction
  * correction = error * pidSetup->proportional + derivate * pidSetup->derivative + integral * pidSetup->integrative;
  
  // Set last error for next iteration
  lastError = error;
  
}

void PID::init() {

  // Init last error to NULL
  lastError = NULL;

  // Init integral to zero
  integral = 0;
  
}

