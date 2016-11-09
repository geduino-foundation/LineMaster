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

void Motors::setup(const Setup & setup) {

  max_speed = setup.motors_max_speed;
  
}

void Motors::setSpeed(const int16_t & correction) {

  uint8_t pwm_sx, pwm_dx;
  
  if (correction > 0) {

    // Calculate PWMs
    pwm_sx = constrain(max_speed, 0, 255);
    pwm_dx = constrain(255 - max_speed + correction, 0, 255);
    
  } else if (correction < 0) {

    // Calculate PWMs
    pwm_sx = constrain(max_speed + correction, 0, 255);
    pwm_dx = constrain(255 - max_speed, 0, 255);
    
  }

  // Set PWMs
  analogWrite(motor_sx_pin, pwm_sx);
  analogWrite(motor_dx_pin, pwm_dx);
  
}

/**
 * This method must be invoked on setup()
 */
void Motors::setMotorPwmFrequency() {

  // Set PWM frequency divider to 1
  setPwmFrequency(motor_sx_pin, 1);
  setPwmFrequency(motor_dx_pin, 1);
  
}

void Motors::stop() {

  // Set PWMs to 128
  analogWrite(motor_sx_pin, 128);
  analogWrite(motor_dx_pin, 128);
  
}

void Motors::init() {

  // Set motor PINs to OUTPUT
  pinMode(motor_sx_pin, OUTPUT);
  pinMode(motor_dx_pin, OUTPUT);

  // Stop motors
  stop();
  
}

