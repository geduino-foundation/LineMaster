#include "QTR8RC.h"

void QTR8RC::calibrate() {

  // The sensor raw values
  unsigned int values[SENSORS_COUNT];

  // Read raw
  readRaw(values);

  for (int index = 0; index < SENSORS_COUNT; index++) {

    if (values[index] < minValues[index]) {

      // Set new min value
      minValues[index] = values[index];

    } else if (values[index] > maxValues[index]) {

      // Set new max value
      maxValues[index] = values[index];

    }

  }

}

void QTR8RC::getCalibration(int index, unsigned int * minValue, unsigned int * maxValue, int * count) {

  // Copy min and max value
  * minValue = minValues[index];
  * maxValue = maxValues[index];
    
  // Set count
  * count = SENSORS_COUNT;
  
}

void QTR8RC::read(unsigned int * values) {

  // The sensor raw values
  unsigned int rawValues[SENSORS_COUNT];

  // Read raw
  readRaw(rawValues);

  for (int index = 0; index < SENSORS_COUNT; index++) {

    if (rawValues[index] < minValues[index]) {

      // Value under min: set 0
      values[index] = 0;

    } else if (rawValues[index] > maxValues[index]) {

      // Value over max: set timeout
      values[index] = SENSOR_TIMEOUT;

    } else {

      // Map value betwen 0 and timeout
      values[index] = map(rawValues[index], minValues[index], maxValues[index], 0, SENSOR_TIMEOUT);

    }
    
  }

}

void QTR8RC::readError(unsigned int * values, int * error, boolean * inLine) {

  // Read
  read(values);

  unsigned long errorSum = 0;
  unsigned long valuesSum = 0;
  * inLine = false;

  for (unsigned int index = 0; index < SENSORS_COUNT; index++) {

    if (! (* inLine) && values[index] > qtr8rcSetup->sensorInLineThreshold) {

      // Set in line to true
      * inLine = true;
      
    }

    if (values[index] > qtr8rcSetup->sensorNoiseThreshold) {
      
      // Sum error and values
      errorSum += (long) index * SENSOR_UNIT * values[index];
      valuesSum += values[index];

    };

  }

  if (* inLine) {

    // Calculate error
    * error = ((int) (errorSum / valuesSum)) - errorOffset;
    
  } else if (lastError > 0) {

    // Calculate error
    * error = errorOffset;
    
  } else if (lastError < 0) {

    // Calculate error
    * error = - errorOffset;
    
  } else {

    // Calculate error
    * error = 0;
    
  }
    
  // Set last error for next iteration
  lastError = * error;
  
}

void QTR8RC::init(unsigned int * _irPins) {

  // Reserve space for ir PINs
  irPins = (unsigned int *) malloc(sizeof(int) * SENSORS_COUNT);

  // Reserve soace for calibration data
  minValues = (unsigned int *) malloc(sizeof(int) * SENSORS_COUNT);
  maxValues = (unsigned int *) malloc(sizeof(int) * SENSORS_COUNT);

  for (int index = 0; index < SENSORS_COUNT; index++) {

    // Set ir pin
    irPins[index] = _irPins[index];

    // Set initial min and max values
    minValues[index] = SENSOR_TIMEOUT;
    maxValues[index] = 0;

  }

  // Set last error to zero
  lastError = 0;

}

void QTR8RC::readRaw(unsigned int * values) {

  for (int index = 0; index < SENSORS_COUNT; index++) {

    // Set value to max (i.e. the timeout)
    values[index] = SENSOR_TIMEOUT;

    // Set ir PIN to OUTPUT and drive it HIGH
    pinMode(irPins[index], OUTPUT);
    digitalWrite(irPins[index], HIGH);

  }

  // Leave time to capacitors to charge
  delayMicroseconds(10);

  for (int index = 0; index < SENSORS_COUNT; index++) {

    // Set ir PIN to INPUT and disable internal pull-up
    pinMode(irPins[index], INPUT);
    digitalWrite(irPins[index], LOW);

  }

  // Get start time
  unsigned int count = 0;
  unsigned long startTime = micros();

  while (micros() - startTime < SENSOR_TIMEOUT && count < SENSORS_COUNT) {

    // Get ellapsed time
    unsigned int ellapsedTime = micros() - startTime;

    for (int index = 0; index < SENSORS_COUNT; index++) {

      // Check if ir PIN is LOW (and it was not LOW before)
      if (digitalRead(irPins[index]) == LOW && ellapsedTime < values[index]) {

        // Set value
        values[index] = ellapsedTime;

        // Increase count
        count++;

      }

    }

  }

}
