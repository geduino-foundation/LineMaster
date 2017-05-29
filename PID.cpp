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

  // Calculate proportional, integrative and derivative correction
  int proportionalCorrection = constrain(error * pidSetup->proportional, - pidSetup->maxProportional, pidSetup->maxProportional);
  int integrativeCorrection = constrain(integral * pidSetup->integrative, - pidSetup->maxIntegrative, pidSetup->maxIntegrative);
  int derivativeCorrection = constrain(derivate * pidSetup->derivative, - pidSetup->maxDerivative, pidSetup->maxDerivative);
  
  // Calculate correction
  * correction = constrain(proportionalCorrection + integrativeCorrection + derivativeCorrection, - pidSetup->maxCorrection, pidSetup->maxCorrection);
 
  // Set last error for next iteration
  lastError = error;
  
}

void PID::init() {

  // Init last error to NULL
  lastError = NULL;

  // Init integral to zero
  integral = 0;
  
}

