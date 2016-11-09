/*
  PID.cpp
  Copyright (C) 2016 Alessandro Francescon

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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

