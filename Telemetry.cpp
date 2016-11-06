#include "Telemetry.h"

void Telemetry::reset() {

  // Full data with zeroes
  memset(data, sizeof(TelemetryData) * size, 0);

  // Reset index
  index = 0;
  
}
 
bool Telemetry::add(const unsigned long & time, const int & error) {

  // Put into data
  data[index++].time = time;
  data[index++].error = error;

  if (index == size) {

    // Reset index
    index = 0;

    return true;
    
  } else {

    return false;
    
  }
  
}

void Telemetry::init() {

  // Reserve space for telemetry data
  data = malloc(sizeof(TelemetryData) * size);

  // Reset
  reset();
  
}

