#ifndef _QTR8RC_H_
#define _QTR8RC_H_

#include <Arduino.h>

#include "types.h"

#define SENSORS_COUNT                 8
#define SENSOR_UNIT                1000
#define SENSOR_TIMEOUT             4000

class QTR8RC {

  public:

    QTR8RC(const uint8_t * _irPins) {
  
      // Initialization
      init(_irPins);
    
    };

    void setup(const Setup & setup);

    void calibrate();

    void getCalibration(const int8_t & index, uint16_t * min_value, uint16_t * max_value, int8_t * count);

    void read(uint16_t * values);

    void readError(uint16_t * values, int16_t * error, bool * in_line);

  private:
  
    const int16_t errorOffset = (int16_t) (SENSORS_COUNT - 1) * SENSOR_UNIT / 2;
    
    int16_t ir_in_line_threshold;
    int16_t ir_noise_threshold;
    
    uint8_t * ir_pins;
    uint16_t * min_values, * max_values;
    int16_t last_error;
    
    void init(uint8_t * _ir_pins);

    void reset();

    void readRaw(uint16_t * values);
  
};

#endif
