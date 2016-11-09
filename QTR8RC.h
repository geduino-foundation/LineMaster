/*
  QTR8RC.h
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
    
    }

    void calibrate();

    void getCalibration(int index, unsigned int * minValue, unsigned int * maxValue, int * count);

    void read(unsigned int * values);

    void readError(unsigned int * values, int * error, boolean * inLine);

  private:

    const int errorOffset = (int) (SENSORS_COUNT - 1) * SENSOR_UNIT / 2;

    const QTR8RCSetup * qtr8rcSetup;
    
    unsigned int * irPins, * minValues, * maxValues;
    int lastError;
    
    void init(unsigned int * _irPins);

    void readRaw(unsigned int * values);
  
};

#endif
