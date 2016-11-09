/*
  Telemetry.cpp
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

#include "Telemetry.h"

void Telemetry::reset() {

  // Full data with zeroes
  memset(data, sizeof(TelemetryData) * size, 0);

  // Reset index
  index = 0;
  
}
 
bool Telemetry::add(const uint32_t & time, const int16_t & error) {

  TelemetryData new_data;
  new_data.time = time;
  new_data.error = error;

  // Put into data
  data[index++] = new_data;

  if (index == size) {

    // Reset index
    index = 0;

    return true;
    
  } else {

    return false;
    
  }
  
}

void Telemetry::init() {

  // Reserve space for telemetry data
  data = malloc(sizeof(TelemetryData) * size);

  // Reset
  reset();
  
}

