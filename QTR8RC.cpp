#include "QTR8RC.h"

void QTR8RC::setup(const Setup & setup) {

   ir_in_line_threshold = setup.ir_in_line_threshold;
   ir_noise_threshold = setup.ir_noise_threshold;
  
}

void QTR8RC::calibrate() {

  // The sensor raw values
  unsigned int values[SENSORS_COUNT];

  // Read raw
  readRaw(values);

  for (int index = 0; index < SENSORS_COUNT; index++) {

    if (values[index] < min_values[index]) {

      // Set new min value
      min_values[index] = values[index];

    } else if (values[index] > max_values[index]) {

      // Set new max value
      max_values[index] = values[index];

    }

  }

}

void QTR8RC::getCalibration(const int & index, unsigned int * min_value, unsigned int * max_value, int * count) {

  // Copy min and max value
  * min_value = min_values[index];
  * max_value = max_values[index];
    
  // Set count
  * count = SENSORS_COUNT;
  
}

void QTR8RC::read(unsigned int * values) {

  // The sensor raw values
  unsigned int raw_values[SENSORS_COUNT];

  // Read raw
  readRaw(raw_values);

  for (int index = 0; index < SENSORS_COUNT; index++) {

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

void QTR8RC::readError(unsigned int * values, int * error, boolean * in_line) {

  // Read
  read(values);

  unsigned long error_sum = 0;
  unsigned long value_sum = 0;
  * in_line = false;

  for (unsigned int index = 0; index < SENSORS_COUNT; index++) {

    if (! (* in_line) && values[index] > ir_in_line_threshold) {

      // Set in line to true
      * in_line = true;
      
    }

    if (values[index] > ir_noise_threshold) {
      
      // Sum error and values
      error_sum += (long) index * SENSOR_UNIT * values[index];
      value_sum += values[index];

    };

  }

  if (* in_line) {

    // Calculate error
    * error = ((int) (error_sum / value_sum)) - errorOffset;
    
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

void QTR8RC::init(unsigned int * _ir_pins) {

  // Reserve space for ir PINs
  ir_pins = (unsigned int *) malloc(sizeof(int) * SENSORS_COUNT);

  // Reserve soace for calibration data
  min_values = (unsigned int *) malloc(sizeof(int) * SENSORS_COUNT);
  max_values = (unsigned int *) malloc(sizeof(int) * SENSORS_COUNT);

  for (int index = 0; index < SENSORS_COUNT; index++) {

    // Set ir pin
    ir_pins[index] = _ir_pins[index];

  }
  
  // Reset
  reset();

}

void QTR8RC::reset() {

  for (int index = 0; index < SENSORS_COUNT; index++) {

    // Set initial min and max values
    min_values[index] = SENSOR_TIMEOUT;
    max_values[index] = 0;

  }

  // Set last error to zero
  last_error = 0;
  
}

void QTR8RC::readRaw(unsigned int * values) {

  for (int index = 0; index < SENSORS_COUNT; index++) {

    // Set value to max (i.e. the timeout)
    values[index] = SENSOR_TIMEOUT;

    // Set ir PIN to OUTPUT and drive it HIGH
    pinMode(ir_pins[index], OUTPUT);
    digitalWrite(ir_pins[index], HIGH);

  }

  // Leave time to capacitors to charge
  delayMicroseconds(10);

  for (int index = 0; index < SENSORS_COUNT; index++) {

    // Set ir PIN to INPUT and disable internal pull-up
    pinMode(ir_pins[index], INPUT);
    digitalWrite(ir_pins[index], LOW);

  }

  // Get start time
  unsigned int count = 0;
  unsigned long start_time = micros();

  while (micros() - start_time < SENSOR_TIMEOUT && count < SENSORS_COUNT) {

    // Get ellapsed time
    unsigned int ellapsed_time = micros() - start_time;

    for (int index = 0; index < SENSORS_COUNT; index++) {

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
