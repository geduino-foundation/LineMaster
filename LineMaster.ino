/*
  LineMaster
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

#include "pinout.h"
#include "Motors.h"
#include "UI.h"
#include "Battery.h"
#include "QTR8RC.h"
#include "PID.h"
#include "SerialSetup.h"

// Comment/uncomment to enable/disable battery check
//#define SKIP_BATERY_CHECK

// The setup timeout in secs
#define SETUP_TIMEOUT 5

// The IR calibration time in millis
#define IR_CALIBRATION_TIME 5000

// The loop cycle duration in millis
#define LOOP_CYCLE_DURATION 5

Settings settings;

PID pid;

Motors motors(MOTOR_SX_PIN, MOTOR_DX_PIN);

UI ui(LED_PIN, BUTTON_PIN);

QTR8RC qtr8rc((int[]) {IR1_PIN, IR2_PIN, IR3_PIN, IR4_PIN, IR5_PIN, IR6_PIN, IR7_PIN, IR8_PIN});

Battery battery(BATTERY_PIN);

SerialSetup serialSetup(& settings, & ui, & battery);

void batteryCheck() {

  // Check battery level
  float volts;
  boolean batteryCheckRrsult = battery.check(& volts);

#ifndef SKIP_BATERY_CHECK
  if (!batteryCheckRrsult) {

    // Fast blink led
    ui.ledBlinkFastFor(0);

  }
#endif

}

void calibrate() {

  // Init calibration parameters
  unsigned long calibrationStartTime = millis();
  unsigned int cycles = 0;

  while (millis() - calibrationStartTime < IR_CALIBRATION_TIME) {

    // Calibrate QTR8RC
    qtr8rc.calibrate();

    // Increase cycle
    cycles++;

  }

}

void setup() {

  // Init serial
  Serial.begin(9600);

  // Set motor PWM frequency
  motors.setMotorPwmFrequency();

  // Battery check
  batteryCheck();

  // Turn led on
  ui.ledOn();

  bool pressed;
  do {

    // Check button pressed
    ui.button(& pressed);

    // Handle serial setup
    serialSetup.handleSerialSetup();
    
  } while (! pressed);

  // Turn led off
  ui.ledOff();

  // Configure PID and QTR8RC
  pid.setup(settings);
  qtr8rc.setup(settings);
  
  // Calibration
  calibrate();

  // Turn led on
  ui.ledOn();

  // Wait for button
  ui.waitButton();

  // Turn led off
  ui.ledOff();

  // Wait 500 millis to give time to... get your finger out!
  delay(500);

}

void loop() {

  boolean stopped, inLine;
  unsigned int values[8];
  int error, motorSx, motorDx;

  long cycleTimestamp = millis(), cycleRemaining;

  do {

    // Read error
    qtr8rc.readError(values, & error, & inLine);

    if (inLine) {

      // Turn led off
      ui.ledOff();

    } else {

      // Turn led on
      ui.ledOn();

    }

    // Update PID controller
    pid.update(error, & motorSx, & motorDx);

    // Set motors speed
    motors.setSpeed(motorSx, motorDx);

    // Get stopped
    ui.button(& stopped);

    // Calculate remaining time in order too meet set cycle duration
    cycleRemaining = LOOP_CYCLE_DURATION - (millis() - cycleTimestamp);

    if (cycleRemaining > 0) {

      // Delat for remaining millis
      delay(cycleRemaining);

      // Turn led off
      ui.ledOff();

    } else {

      // Turn led on
      ui.ledOn();

    }

    // Set cycle timestamp
    cycleTimestamp = millis();

  } while (!stopped);

  // Stop motors
  motors.stop();

  // Slow blink led
  ui.ledBlinkSlowFor(0);

}

