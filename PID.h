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

#include <Arduino.h>

struct PidSetup {
    float proportional;
    int maxProportional;
    float integrative;
    int maxIntegrative;
    float derivative;
    int maxDerivative;
    int maxCorrection;
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

    unsigned long lastMicros;
    int lastError;
    long integral;
  
};

#endif
