/*
  serial_setup.h
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

#ifndef _SERIAL_SETUP_H_
#define _SERIAL_SETUP_H_

#include <Arduino.h>

void emptySerial() {

  // Empty incoming serial buffer
  while (Serial.available() > 0) {
    Serial.read();
  }
  
}

void serialPromptFloat(const char * prompt, float * value, const int decimals) {

  // Empty serial
  emptySerial();
  
  // Prompt
  Serial.print(prompt);
  Serial.print(" (");
  Serial.print(* value, decimals);
  Serial.print("): ");

  // Wait data
  while (Serial.available() == 0) {
  }
  
  // Parse received serial bytes
  * value = Serial.parseFloat();

  // Print
  Serial.println(* value, decimals);
  
}

void serialPromptInt(const char * prompt, int * value) {

  // Empty serial
  emptySerial();

  // Prompt
  Serial.print(prompt);
  Serial.print(" (");
  Serial.print(* value);
  Serial.print("): ");

  // Wait data
  while (Serial.available() == 0) {
  }
  
  // Parse received serial bytes
  * value = Serial.parseInt();

  // Print
  Serial.println(* value);
  
}

void serialPromptYesNo(const char * prompt, boolean * value) {

  // Empty serial
  emptySerial();

  // Prompt
  Serial.print(prompt);
  Serial.print(" (y/n) ? ");

  // Wait data
  while (Serial.available() == 0) {
  }

   // Read response
  byte response = Serial.read();
 * value = response == 0x79 || response == 59;

  // Print
  Serial.println((* value) ? "y" : "n");
  
}
#endif
