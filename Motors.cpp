/*
  Motors.cpp
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

#include "Motors.h"
#include "pwm_frequency.h";

void Motors::setSpeed(const int correction) {

  byte pwmSx, pwmDx;
  
  if (correction > 0) {

    // Calculate PWMs
    pwmSx = constrain(motorsSetup->normalSpeed + correction, 0, motorsSetup->maxSpeed);
    pwmDx = constrain(pwmSx - correction, 0, motorsSetup->maxSpeed);
    
  } else if (correction < 0) {

    // Calculate PWMs
    pwmDx = constrain(motorsSetup->normalSpeed - correction, 0, motorsSetup->maxSpeed);
    pwmSx = constrain(pwmDx + correction, 0, motorsSetup->maxSpeed);
    
  } else {

    // Calculate PWMs
    pwmSx = motorsSetup->normalSpeed;
    pwmDx = motorsSetup->normalSpeed;
    
  }

  // Set PWMs
  analogWrite(motorSxPin, pwmSx);
  analogWrite(motorDxPin, 255 - pwmDx);
  
}

/**
 * This method must be invoked on setup()
 */
void Motors::setMotorPwmFrequency() {

  // Set PWM frequency divider to 1
  setPwmFrequency(motorSxPin, 1);
  setPwmFrequency(motorDxPin, 1);
  
}

void Motors::stop() {

  // Set PWMs to 128
  analogWrite(motorSxPin, 128);
  analogWrite(motorDxPin, 128);
  
}

void Motors::init() {

  // Set motor PINs to OUTPUT
  pinMode(motorSxPin, OUTPUT);
  pinMode(motorDxPin, OUTPUT);

  // Stop motors
  stop();
  
}

