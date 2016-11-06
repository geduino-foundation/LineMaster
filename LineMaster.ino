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
#include "Telemetry.h"

// Comment/uncomment to enable/disable battery check
//#define SKIP_BATERY_CHECK

// The setup timeout in secs
#define SETUP_TIMEOUT 5

// The IR calibration time in millis
#define IR_CALIBRATION_TIME 5000

// The loop cycle duration in millis
#define LOOP_CYCLE_DURATION 5

// The telemetry buffer size
#define TELEMETRY_BUFFER_SIZE 200

Setup _setup;

PID pid;

Motors motors(MOTOR_SX_PIN, MOTOR_DX_PIN);

UI ui(LED_PIN, BUTTON_PIN);

QTR8RC qtr8rc((int8_t[]) {IR1_PIN, IR2_PIN, IR3_PIN, IR4_PIN, IR5_PIN, IR6_PIN, IR7_PIN, IR8_PIN});

Battery battery(BATTERY_PIN);

Telemetry telemetry(TELEMETRY_BUFFER_SIZE);

SerialSetup serial_setup(& _setup, & ui, & battery, & telemetry);

void doBatteryCheck() {

  // Check battery level
  float volts;
  bool battery_check_result = battery.check(& volts);

#ifndef SKIP_BATERY_CHECK
  if (!battery_check_result) {

    // Fast blink led
    ui.ledBlinkFastFor(0);

  }
#endif

}

void doCalibrate() {

  // Init calibration parameters
  uint32_t calibration_start_time = millis();
  uint16_t cycles = 0;

  while (millis() - calibration_start_time < IR_CALIBRATION_TIME) {

    // Calibrate QTR8RC
    qtr8rc.calibrate();

    // Increase cycle
    cycles++;

  }

}

void doSerialSetup() {

  // Turn led on
  ui.ledOn();
  
  bool pressed;
  do {

    // Check button pressed
    ui.button(& pressed);

    // Handle serial setup
    serial_setup.handleSerialSetup();
    
  } while (! pressed);

  // Turn led off
  ui.ledOff();
  
}

void setup() {

  // Init serial
  Serial.begin(9600);

  // Set motor PWM frequency
  motors.setMotorPwmFrequency();

  // Battery check
  doBatteryCheck();
  
  // Serial setup
  doSerialSetup();

  // Configure PID, QTR8RC and Motors
  pid.setup(_setup);
  qtr8rc.setup(_setup);
  motors.setup(_setup);

  // Reset telemetry
  telemetry.reset();
  
  // Calibration
  doCalibrate();
  
}

void loop() {

   // Turn led on
  ui.ledOn();

  // Wait for button
  ui.waitButton();

  // Turn led off
  ui.ledOff();

  // Give time to move finger away...
  delay(1000);

  bool stopped, in_line;
  uint16_t values[8];
  int16_t error, correction;
  uint32_t cycle_start_time;
  int32_t cycle_remaining;

  do {

    cycle_start_time = millis();

    // Read error
    qtr8rc.readError(values, & error, & in_line);

    if (in_line) {

      // Turn led off
      ui.ledOff();

    } else {

      // Turn led on
      ui.ledOn();

    }

    // Update PID controller
    pid.update(error, & correction);

    // Check if telemetry in enabled
    if (_setup.telemetry_enabled) {

      // Add to telemetry and check if buffer is full
      if (telemetry.add(cycle_start_time, error)) {

        // Interrupt run
        break;
        
      }
      
    }
    
    // Set motors speed
    motors.setSpeed(correction);

    // Get stopped
    ui.button(& stopped);

    // Calculate remaining time in order too meet set cycle duration
    cycle_remaining = LOOP_CYCLE_DURATION - (millis() - cycle_start_time);

    if (cycle_remaining > 0) {

      // Delat for remaining millis
      delay(cycle_remaining);

      // Turn led off
      ui.ledOff();

    } else {

      // Turn led on
      ui.ledOn();

    }

  } while (!stopped);

  // Stop motors
  motors.stop();

  // Turn led off
  ui.ledOff();

  // Give time to move finger away...
  delay(1000);

  // Serial setup
  doSerialSetup();

  // Configure PID, QTR8RC and Motors
  pid.setup(_setup);
  qtr8rc.setup(_setup);
  motors.setup(_setup);

}

