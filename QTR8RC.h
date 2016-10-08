#ifndef _QTR8RC_H_
#define _QTR8RC_H_

#include <Arduino.h>

#define SENSORS_COUNT                 8
#define SENSOR_UNIT                1000
#define SENSOR_TIMEOUT             4000
#define SENSOR_IN_LINE_THRESHOLD   1000
#define SENSOR_NOISE_THRESHOLD       50

class QTR8RC {

  public:

    QTR8RC(unsigned int * _irPins) {
  
      // Initialization
      init(_irPins);
    
    };

    void calibrate();

    void getCalibration(int index, unsigned int * minValue, unsigned int * maxValue, int * count);

    void read(unsigned int * values);

    void readError(int * error);

  private:

    const int errorOffset = (int) (SENSORS_COUNT - 1) * SENSOR_UNIT / 2;
    
    unsigned int * irPins, * minValues, * maxValues;
    int lastError;
    
    void init(unsigned int * _irPins);

    void readRaw(unsigned int * values);
  
};

#endif
