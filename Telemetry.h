/*
  Telemetry.h
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

#ifndef _TELEMETRY_H_
#define _TELEMETRY_H_

#include <Arduino.h>

#include "types.h"

class Telemetry {

  public:

    const uint16_t size;

    TelemetryData * data;

    Telemetry(const uint16_t _size) :
      size(_size) {
      
      // Initialization
      this->init();
    
    }

    void reset();

    bool add(const uint32_t & time, const int16_t & error);
    
  private:

    uint16_t index;
    
    void init();
  
};

#endif
