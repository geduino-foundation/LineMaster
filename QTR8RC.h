#ifndef _QTR8RC_H_
#define _QTR8RC_H_

#include <Arduino.h>

#define SENSORS_COUNT                 8
#define SENSOR_UNIT                1000
#define SENSOR_TIMEOUT             4000

struct QTR8RCSetup {
    int sensorInLineThreshold;
    int sensorNoiseThreshold;
};

class QTR8RC {

  public:

    QTR8RC(unsigned int * _irPins, const QTR8RCSetup * _qtr8rcSetup) :
      qtr8rcSetup(_qtr8rcSetup) {
  
      // Initialization
      init(_irPins);
    
    };

    void calibrate();

    void getCalibration(int index, unsigned int * minValue, unsigned int * maxValue, int * count);

    void read(unsigned int * values);

    void readError(int * error);

  private:

    const int errorOffset = (int) (SENSORS_COUNT - 1) * SENSOR_UNIT / 2;

    const QTR8RCSetup * qtr8rcSetup;
    
    unsigned int * irPins, * minValues, * maxValues;
    int lastError;
    
    void init(unsigned int * _irPins);

    void readRaw(unsigned int * values);
  
};

#endif
