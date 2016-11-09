/*
  Motors.h
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

#ifndef _MOTORS_H_
#define _MOTORS_H_

#include <Arduino.h>

#include "types.h"

class Motors {

  public:

    Motors(const int8_t _motor_sx_pin, const int8_t _motor_dx_pin) :
      motor_sx_pin(_motor_sx_pin), motor_dx_pin(_motor_dx_pin) {
      
      // Initialization
      this->init();
    
    }

    void setMotorPwmFrequency();

    void setup(const Setup & setup);
    
    void setSpeed(const int16_t & correction);

    void stop();

  private:

    const uint8_t motor_sx_pin, motor_dx_pin;

    uint8_t max_speed;

    void init();
  
};

#endif
