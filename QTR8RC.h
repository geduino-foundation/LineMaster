#ifndef _QTR8RC_H_
#define _QTR8RC_H_

#include <Arduino.h>

#include "types.h"

#define SENSORS_COUNT                 8
#define SENSOR_UNIT                1000
#define SENSOR_TIMEOUT             4000

class QTR8RC {

  public:

    QTR8RC(const unsigned int * _irPins) {
  
      // Initialization
      init(_irPins);
    
    };

    void setup(const Setup & setup);

    void calibrate();

    void getCalibration(const int & index, unsigned int * min_value, unsigned int * max_value, int * count);

    void read(unsigned int * values);

    void readError(unsigned int * values, int * error, boolean * in_line);

  private:
  
    const int errorOffset = (int) (SENSORS_COUNT - 1) * SENSOR_UNIT / 2;
    
    int ir_in_line_threshold;
    int ir_noise_threshold;
    
    unsigned int * ir_pins, * min_values, * max_values;
    int last_error;
    
    void init(unsigned int * _ir_pins);

    void reset();

    void readRaw(unsigned int * values);
  
};

#endif
