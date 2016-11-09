/*
  PID.h
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

#ifndef _PID_H_
#define _PID_H_

#ifdef ARDUINO
#include <Arduino.h>
#endif

#include "types.h"

#ifndef ARDUINO
#define NULL __null
#define constrain(v, a, b) ((v < a) ? a : (v > b) ? b : v)
#endif

class PID {

  public:

    PID() {
      
      // Initialization
      this->init();
    
    }
    
    void setup(const Setup & setup);
    
    void update(const int16_t & error, int16_t * correction);
    
  private:

    float proportional;
    float integrative;
    float derivative;
    int16_t pid_max_proportional;
    int16_t pid_max_integrative;
    int16_t pid_max_derivative; 
    int16_t pid_max_correction;
    
    int16_t last_error;
    int32_t integral;
    
    void init();

    void reset();
  
};

#endif
