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
#include "serial_setup.h"

// Comment/uncomment to enable/disable battery check
//#define SKIP_BATERY_CHECK

// The setup timeout in secs
#define SETUP_TIMEOUT 5

// The IR calibration time in millis
#define IR_CALIBRATION_TIME 5000

PidSetup pidSetup;
QTR8RCSetup qtr8rcSetup;

PID pid(& pidSetup);

Motors motors(MOTOR_SX_PIN, MOTOR_DX_PIN);

UI ui(LED_PIN, BUTTON_PIN);

QTR8RC qtr8rc((int[]) {IR1_PIN, IR2_PIN, IR3_PIN, IR4_PIN, IR5_PIN, IR6_PIN, IR7_PIN, IR8_PIN}, & qtr8rcSetup);

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
  eeprom_write_block((const void *) & qtr8rcSetup, (void *) sizeof(pidSetup), sizeof(qtr8rcSetup));

  // Print
  Serial.println("Setup saved in EEPROM");
  
}

void loadSetup() {

  // Read from EEPROM
  eeprom_read_block((void *) & pidSetup, (void *) 0, sizeof(pidSetup));
  eeprom_read_block((void *) & qtr8rcSetup, (void *) sizeof(pidSetup), sizeof(qtr8rcSetup));

  // Print
  Serial.println("Setup loaded from EEPROM");
  
}

void serialSetup() {
  
  // Prompt proportinal factor
  serialPromptFloat("Enter PID proportional factor)", & pidSetup.proportional, 6);

  // Prompt integrative factor
  serialPromptFloat("Enter PID integrative factor)", & pidSetup.integrative, 6);

  // Prompt derivative factor
  serialPromptFloat("Enter PID derivative factor)", & pidSetup.derivative, 6);

  // Prompt motor max speed
  serialPromptInt("Enter motor max speed in [-127, 128] range", & pidSetup.motorMaxSpeed);
  
  // Prompt motor max correction factor
  serialPromptInt("Enter motor max correction in [0, 256] range", & pidSetup.motorMaxCorrection);

  // Prompt QTR8RC sensor in line threshold
  serialPromptInt("Enter QTR8RC sensor in line threshold [0, 4000] range", & qtr8rcSetup.sensorInLineThreshold);
  
  // Prompt QTR8RC sensor noise threshold
  serialPromptInt("Enter QTR8RC sensor noise threshold [0, 4000] range", & qtr8rcSetup.sensorNoiseThreshold);

  // Prompt for save
  boolean save = false;
  serialPromptYesNo("Do you want to store this setup in EEPROM", & save);

  if (save) {

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
  Serial.setTimeout(1500);

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

