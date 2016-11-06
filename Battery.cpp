#include "Battery.h"

#define BATTERY_RAW_TO_VOLT   0.009706
#define BATTERY_MIN_VOLTS     7.4

void Battery::readVoltage(float * volts) {

  int16_t raw = 0;
  
  for (uint16_t index = 0; index < 10; index++) {
    
    // Read raw value
    raw += analogRead(battery_pin);

    // Just wait for stabilization
    delay(50);
  
  }

  // Convert to volts
  * volts = raw / 10 * BATTERY_RAW_TO_VOLT;
  
}

bool Battery::check(float * volts) {

  // Read voltage
  readVoltage(volts);

  return * volts > BATTERY_MIN_VOLTS;
  
}

void Battery::init() {

  // Set battery PIN to INPUT
  pinMode(battery_pin, INPUT);
  
}

