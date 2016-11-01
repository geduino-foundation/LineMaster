#include "PID.h"

void PID::setup(Settings settings) {

  proportional = settings.pidProportional / 10000.0;
  integrative = settings.pidIntegrative / 10000.0;
  derivative = settings.pidDerivative / 10000.0;
  motorsMaxSpeed = settings.motorsMaxSpeed;
  
}

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
  * motorSx = motorsMaxSpeed;
  * motorDx = motorsMaxSpeed;

  // Calculate correction
  int correction = error * proportional + derivate * derivative + integral * integrative;

  if (correction > 0) {

    // Apply correction
    * motorDx = motorsMaxSpeed - correction;
    
  } else if (correction < 0) {

    // Apply correction
    * motorSx = motorsMaxSpeed + correction;
    
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

