/*
  QTR8RC.cpp
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

#include "QTR8RC.h"

void QTR8RC::setup(const Setup & setup) {

   ir_in_line_threshold = setup.ir_in_line_threshold;
   ir_noise_threshold = setup.ir_noise_threshold;
  
}

void QTR8RC::calibrate() {

  // The sensor raw values
  uint16_t values[SENSORS_COUNT];

  // Read raw
  readRaw(values);

  for (uint8_t index = 0; index < SENSORS_COUNT; index++) {

    if (values[index] < min_values[index]) {

      // Set new min value
      min_values[index] = values[index];

    } else if (values[index] > max_values[index]) {

      // Set new max value
      max_values[index] = values[index];

    }

  }

}

void QTR8RC::getCalibration(const int8_t & index, uint16_t * min_value, uint16_t * max_value, int8_t * count) {

  // Copy min and max value
  * min_value = min_values[index];
  * max_value = max_values[index];
    
  // Set count
  * count = SENSORS_COUNT;
  
}

void QTR8RC::read(uint16_t * values) {

  // The sensor raw values
  uint16_t raw_values[SENSORS_COUNT];

  // Read raw
  readRaw(raw_values);

  for (uint8_t index = 0; index < SENSORS_COUNT; index++) {

    if (raw_values[index] < min_values[index]) {

      // Value under min: set 0
      values[index] = 0;

    } else if (raw_values[index] > max_values[index]) {

      // Value over max: set timeout
      values[index] = SENSOR_TIMEOUT;

    } else {

      // Map value betwen 0 and timeout
      values[index] = map(raw_values[index], min_values[index], max_values[index], 0, SENSOR_TIMEOUT);

    }
    
  }

}

void QTR8RC::readError(uint16_t * values, int16_t * error, bool * in_line) {

  // Read
  read(values);

  uint32_t error_sum = 0;
  uint32_t value_sum = 0;
  * in_line = false;

  for (uint8_t index = 0; index < SENSORS_COUNT; index++) {

    if (! (* in_line) && values[index] > ir_in_line_threshold) {

      // Set in line to true
      * in_line = true;
      
    }

    if (values[index] > ir_noise_threshold) {
      
      // Sum error and values
      error_sum += (int32_t) index * SENSOR_UNIT * values[index];
      value_sum += values[index];

    };

  }

  if (* in_line) {

    // Calculate error
    * error = ((int16_t) (error_sum / value_sum)) - errorOffset;
    
  } else if (last_error > 0) {

    // Calculate error
    * error = errorOffset;
    
  } else if (last_error < 0) {

    // Calculate error
    * error = - errorOffset;
    
  } else {

    // Calculate error
    * error = 0;
    
  }
    
  // Set last error for next iteration
  last_error = * error;
  
}

void QTR8RC::init(uint8_t * _ir_pins) {

  // Reserve space for ir PINs
  ir_pins = (uint8_t *) malloc(sizeof(uint8_t) * SENSORS_COUNT);

  // Reserve soace for calibration data
  min_values = (uint16_t *) malloc(sizeof(uint16_t) * SENSORS_COUNT);
  max_values = (uint16_t *) malloc(sizeof(uint16_t) * SENSORS_COUNT);

  for (uint8_t index = 0; index < SENSORS_COUNT; index++) {

    // Set ir pin
    ir_pins[index] = _ir_pins[index];

  }
  
  // Reset
  reset();

}

void QTR8RC::reset() {

  for (uint8_t index = 0; index < SENSORS_COUNT; index++) {

    // Set initial min and max values
    min_values[index] = SENSOR_TIMEOUT;
    max_values[index] = 0;

  }

  // Set last error to zero
  last_error = 0;
  
}

void QTR8RC::readRaw(uint16_t * values) {

  for (uint8_t index = 0; index < SENSORS_COUNT; index++) {

    // Set value to max (i.e. the timeout)
    values[index] = SENSOR_TIMEOUT;

    // Set ir PIN to OUTPUT and drive it HIGH
    pinMode(ir_pins[index], OUTPUT);
    digitalWrite(ir_pins[index], HIGH);

  }

  // Leave time to capacitors to charge
  delayMicroseconds(10);

  for (uint8_t index = 0; index < SENSORS_COUNT; index++) {

    // Set ir PIN to INPUT and disable internal pull-up
    pinMode(ir_pins[index], INPUT);
    digitalWrite(ir_pins[index], LOW);

  }

  // Get start time
  uint16_t count = 0;
  uint32_t start_time = micros();

  while (micros() - start_time < SENSOR_TIMEOUT && count < SENSORS_COUNT) {

    // Get ellapsed time
    uint16_t ellapsed_time = micros() - start_time;

    for (uint8_t index = 0; index < SENSORS_COUNT; index++) {

      // Check if ir PIN is LOW (and it was not LOW before)
      if (digitalRead(ir_pins[index]) == LOW && ellapsed_time < values[index]) {

        // Set value
        values[index] = ellapsed_time;

        // Increase count
        count++;

      }

    }

  }

}
