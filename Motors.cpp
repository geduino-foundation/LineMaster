#include "Motors.h"
#include "pwm_frequency.h";

void Motors::setup(const Setup & setup) {

  max_speed = setup.motors_max_speed;
  
}

void Motors::setSpeed(const int & correction) {

  byte pwm_sx, pwm_dx;
  
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

