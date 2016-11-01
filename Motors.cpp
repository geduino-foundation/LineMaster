#include "Motors.h"
#include "pwm_frequency.h";

void Motors::setSpeed(const int vSx, const int vDx) {

  // Calculate PWMs
  byte pwmSx = constrain(128 + vSx, 0, 255);
  byte pwmDx = constrain(128 - vDx, 0, 255);

  // Set PWMs
  analogWrite(motorSxPin, pwmSx);
  analogWrite(motorDxPin, pwmDx);
  
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

