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
