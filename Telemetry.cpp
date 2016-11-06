#include "Telemetry.h"

void Telemetry::reset() {

  // Full data with zeroes
  memset(data, sizeof(TelemetryData) * size, 0);

  // Reset index
  index = 0;
  
}
 
bool Telemetry::add(const uint32_t & time, const int16_t & error) {

  TelemetryData new_data;
  new_data.time = time;
  new_data.error = error;

  // Put into data
  data[index++] = new_data;

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

