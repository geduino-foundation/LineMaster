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

void PID::setup(const Setup & setup) {

  proportional = setup.pid_proportional / 10000.0;
  integrative = setup.pid_integrative / 10000.0;
  derivative = setup.pid_derivative / 10000.0;
  pid_max_proportional = setup.pid_max_proportional;
  pid_max_integrative = setup.pid_max_integrative;
  pid_max_derivative = setup.pid_max_derivative; 
  pid_max_correction = setup.pid_max_correction;
  
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

  // Calculate proportional, integrative and derivative correction
  int16_t proportional_correction = constrain(error * proportional, - pid_max_proportional, pid_max_proportional);
  int16_t integrative_correction = constrain(integral * integrative, - pid_max_integrative, pid_max_integrative);
  int16_t derivative_correction = constrain(derivate * derivative, - pid_max_derivative, pid_max_derivative);
  
  // Calculate correction
  * correction = constrain(proportional_correction + integrative_correction + derivative_correction, - pid_max_correction, pid_max_correction);
  
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
