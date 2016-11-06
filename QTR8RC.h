#ifndef _QTR8RC_H_
#define _QTR8RC_H_

#include <Arduino.h>

#include "SerialSetup.h"

#define SENSORS_COUNT                 8
#define SENSOR_UNIT                1000
#define SENSOR_TIMEOUT             4000

class QTR8RC {

  public:

    QTR8RC(unsigned int * _irPins) {
  
      // Initialization
      init(_irPins);
    
    };

    void setup(Settings settings);

    void calibrate();

    void getCalibration(int index, unsigned int * minValue, unsigned int * maxValue, int * count);

    void read(unsigned int * values);

    void readError(unsigned int * values, int * error, boolean * inLine);

  private:
  
    const int errorOffset = (int) (SENSORS_COUNT - 1) * SENSOR_UNIT / 2;
    
    int sensorInLineThreshold;
    int sensorNoiseThreshold;
    
    unsigned int * irPins, * minValues, * maxValues;
    int lastError;
    
    void init(unsigned int * _irPins);

    void reset();

    void readRaw(unsigned int * values);
  
};

#endif
