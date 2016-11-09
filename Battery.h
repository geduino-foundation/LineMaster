/*
  Battery.h
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

#ifndef _BATTERY_H_
#define _BATTERY_H_

#include <Arduino.h>

class Battery {

  public:

    Battery(const uint8_t _battery_pin) :
      battery_pin(_battery_pin) {
      
      // Initialization
      init();
    
    }

    void readVoltage(float * volts);

    bool check(float * volts);

  private:

    const uint8_t battery_pin;

    void init();
  
};

#endif
