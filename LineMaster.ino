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
#include "eeprom_anything.h"

// Comment/uncomment to enable/disable battery check
//#define SKIP_BATERY_CHECK

// The setup timeout in secs
#define SETUP_TIMEOUT 5

// The IR calibration time in millis
#define IR_CALIBRATION_TIME 5000

PidSetup pidSetup;

PID pid(& pidSetup);

Motors motors(MOTOR_SX_PIN, MOTOR_DX_PIN);

UI ui(LED_PIN, BUTTON_PIN);

QTR8RC qtr8rc((int[]) {IR1_PIN, IR2_PIN, IR3_PIN, IR4_PIN, IR5_PIN, IR6_PIN, IR7_PIN, IR8_PIN});

Battery battery(BATTERY_PIN);

void batteryCheck() {

  // Print
  Serial.print("Checking battery level... ");
   
  // Check battery level
  float volts;
  boolean batteryCheckRrsult = battery.check(& volts);

  // Print
  Serial.println("done!");
  Serial.print("Battery level is: ");
  Serial.print(volts);
  Serial.println(" volt");

#ifndef SKIP_BATERY_CHECK
  if (!batteryCheckRrsult) {

    // Debug
    Serial.print("Battery level is too low: ");
    Serial.print(volts);
    Serial.println(" volt");

    // End serial
    Serial.end();

    while (true) {

      // Fast blink led
      ui.ledBlinkFast();

      // Just for delay
      delay(100);
      
    }
    
  }
#else
  // Debug
  Serial.println("WARNING: battery level check is disabled!");
#endif

}

void saveSetup() {

  // Write to EEPROM
  eeprom_write_block((const void *) & pidSetup, (void *) 0, sizeof(pidSetup));

  // Print
  Serial.println("Setup saved in EEPROM");
  
}

void loadSetup() {

  // Read from EEPROM
  eeprom_read_block((void *) & pidSetup, (void *) 0, sizeof(pidSetup));

  // Print
  Serial.println("Setup loaded from EEPROM");
  
}

void serialSetup() {

  // Empty incoming serial buffer
  while (Serial.available() > 0) {
    Serial.read();
  }

  // Print
  Serial.println("Entering serial setup");
  Serial.print("Enter PID proportinal factor (");
  Serial.print(pidSetup.proportional, 6);
  Serial.print("): ");

  // Wait data
  while (Serial.available() == 0) {
  }
  
  // Parse proportinal factor
  pidSetup.proportional = Serial.parseFloat();

  // Print
  Serial.println(pidSetup.proportional, 6);
  Serial.print("Enter PID integrative factor (");
  Serial.print(pidSetup.integrative, 6);
  Serial.print("): ");

  // Wait data
  while (Serial.available() == 0) {
  }
  
  // Parse integrative factor
  pidSetup.integrative = Serial.parseFloat();
  
  // Print
  Serial.println(pidSetup.integrative, 6);
  Serial.print("Enter PID derivative factor (");
  Serial.print(pidSetup.derivative, 6);
  Serial.print("): ");

  // Wait data
  while (Serial.available() == 0) {
  }
  
  // Parse derivative factor
  pidSetup.derivative = Serial.parseFloat();

  // Print
  Serial.println(pidSetup.derivative, 6);
  Serial.print("Enter motor max speed in [-127, 128] range (");
  Serial.print(pidSetup.motorMaxSpeed);
  Serial.print("): ");

  // Wait data
  while (Serial.available() == 0) {
  }
  
  // Parse motor max speed factor
  pidSetup.motorMaxSpeed = Serial.parseInt();

  // Print
  Serial.println(pidSetup.motorMaxSpeed);
  Serial.print("Enter motor max correction in [0, 256] range (");
  Serial.print(pidSetup.motorMaxCorrection);
  Serial.print("): ");

  // Wait data
  while (Serial.available() == 0) {
  }
  
  // Parse motor max correction factor
  pidSetup.motorMaxCorrection = Serial.parseInt();

  // Print
  Serial.println(pidSetup.motorMaxCorrection);
  Serial.println("Do you want to store this setup in EEPROM (y/n) ?");

  // Wait data
  while (Serial.available() == 0) {
  }

  // Read response
  byte response = Serial.read();

  if (response == 0x79 || response == 59) {

    // Save setup
    saveSetup();
    
  }
  
  
}

void startSetup() {

  // Print
  Serial.print("Press any key to start setup... ");

  // Empty incoming serial buffer
  while (Serial.available() > 0) {
    Serial.read();
  }

  bool enterSetup = false;
  
  for (int index = 0; index < SETUP_TIMEOUT; index++) {

    // Wait one sec
    delay(1000);

    // Print
    Serial.print(SETUP_TIMEOUT - index);
    Serial.print("... ");

    if (Serial.available() > 0) {

      // Set enter setup to true
      enterSetup = true;

      break;
      
    }
    
  }

  // Print
  Serial.println("");

  if (enterSetup) {

      // Serial setup
      serialSetup();

  }
  
}

void calibrate() {

  // Print
  Serial.println("Press button to start calibration...");

  // Turn led on
  ui.ledOn();

  // Wait for button
  ui.waitButton();

  // Turn led off
  ui.ledOff();

  // Print
  Serial.print("Calibration (it will take ");
  Serial.print(IR_CALIBRATION_TIME);
  Serial.print(" millis)... ");

  // Init calibration parameters
  unsigned long calibrationStartTime = millis();
  unsigned int cycles = 0;

  while (millis() - calibrationStartTime < IR_CALIBRATION_TIME) {

    // Calibrate QTR8RC
    qtr8rc.calibrate();

    // Increase cycle
    cycles++;
    
  }

  // Print
  Serial.println("done!");

  // Calculate calibration frequency
  float calibrationFrequency = cycles * 1000.0 / IR_CALIBRATION_TIME;

  // Print
  Serial.print("Calibration frequency: ");
  Serial.print(calibrationFrequency, 2);
  Serial.println(" Hz");

  unsigned int minValue, maxValue;
  int index = 0;
  int count;

  do {

    // Get calibration
    qtr8rc.getCalibration(index, & minValue, & maxValue, & count);

    // Print
    Serial.print("IR ");
    Serial.print(index);
    Serial.print(" of ");
    Serial.print(count);
    Serial.print(" - min: ");
    Serial.print(minValue);
    Serial.print(" - max: ");
    Serial.println(maxValue);
    
  } while (++index < count);
  
}

void setup() {

  // Set motor PWM frequency
  motors.setMotorPwmFrequency();

  // Init serial
  Serial.begin(9600);

  // Print
  Serial.println("LineMaster V1 by Geduino Foundation");
  Serial.println("Copyright (C) 2016 Alessandro Francescon");
 
  // Battery check
  batteryCheck();

  // Load setup
  loadSetup();

  // Setup
  startSetup();
  
  // Calibration
  calibrate();

  // Print
  Serial.println("Press button to start race... ");

  // Turn led on
  ui.ledOn();

  // Wait for button
  ui.waitButton();

  // Turn led off
  ui.ledOff();

  // Debug
  Serial.println("Go Line Master go!!!");

  // End serial
  Serial.end();

  // Wait 500 millis to give time to... get your finger out!
  delay(500);
  
}

void loop() {

  boolean stopped;
  int error, motorSx, motorDx;
   
  do {  
    
    // Read error
    qtr8rc.readError(& error);
  
    // Update PID controller
    pid.update(error, & motorSx, & motorDx);
  
    // Set motors speed
    motors.setSpeed(motorSx, motorDx);
    
    // Get stopped
    ui.button(& stopped);

  } while (!stopped);

  // Stop motors
  motors.stop();

  while (true) {

    // Fast blink led
    ui.ledBlinkSlow();

    // Just for delay
    delay(500);
    
  }
  
}

