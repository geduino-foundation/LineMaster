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

struct MotorsSetup {
    byte normalSpeed;
    byte maxSpeed;
};

class Motors {

  public:

    Motors(const int _motorSxPin, const int _motorDxPin, const MotorsSetup * _motorsSetup) :
      motorSxPin(_motorSxPin), motorDxPin(_motorDxPin), motorsSetup(_motorsSetup) {
      
      // Initialization
      this->init();
    
    }

    void setMotorPwmFrequency();
    
    void setSpeed(const int correction);

    void stop();

  private:

    const MotorsSetup * motorsSetup;

    const unsigned int motorSxPin, motorDxPin;

    void init();
  
};

#endif
