#include "Battery.h"

#define BATTERY_RAW_TO_VOLT   0.009706
#define BATTERY_MIN_VOLTS     7.4

boolean Battery::check(float * volts) {

  int raw = 0;
  
  for (int index = 0; index < 10; index++) {
    
    // Read raw value
    raw += analogRead(batteryPin);

    // Just wait for stabilization
    delay(50);
  
  }

  // Convert to volts
  *volts = raw / 10 * BATTERY_RAW_TO_VOLT;

  return *volts > BATTERY_MIN_VOLTS;
  
}

void Battery::init() {

  // Set battery PIN to INPUT
  pinMode(batteryPin, INPUT);
  
}

