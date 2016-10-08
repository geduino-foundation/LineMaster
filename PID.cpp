#include "PID.h"

void PID::update(int error, int * motorSx, int * motorDx) {

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

  // Set motoir speed to max
  * motorSx = pidSetup->motorMaxSpeed;
  * motorDx = pidSetup->motorMaxSpeed;

  // Calculate correction
  int correction = error * pidSetup->proportional + derivate * pidSetup->derivative + integral * pidSetup->integrative;

  if (correction > 0) {

    // Apply correction
    * motorDx = pidSetup->motorMaxSpeed - constrain(correction, 0, pidSetup->motorMaxCorrection);
    
  } else if (correction < 0) {

    // Apply correction
    * motorSx = pidSetup->motorMaxSpeed + constrain(correction, - pidSetup->motorMaxCorrection, 0);
    
  }
  
  // Set last error for next iteration
  lastError = error;
  
}

void PID::init() {

  // Init last error to NULL
  lastError = NULL;

  // Init integral to zero
  integral = 0;
  
}

