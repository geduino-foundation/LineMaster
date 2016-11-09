/*
  Battery.cpp
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

#include "Battery.h"

#define BATTERY_RAW_TO_VOLT   0.009706
#define BATTERY_MIN_VOLTS     7.4

void Battery::readVoltage(float * volts) {

  int raw = 0;
  
  for (int index = 0; index < 10; index++) {
    
    // Read raw value
    raw += analogRead(batteryPin);

    // Just wait for stabilization
    delay(50);
  
  }

  // Convert to volts
  * volts = raw / 10 * BATTERY_RAW_TO_VOLT;
  
}

boolean Battery::check(float * volts) {

  // Read voltage
  readVoltage(volts);

  return * volts > BATTERY_MIN_VOLTS;
  
}

void Battery::init() {

  // Set battery PIN to INPUT
  pinMode(batteryPin, INPUT);
  
}

