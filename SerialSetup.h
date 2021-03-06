/*
  SerialSetup.h
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

#ifndef _SERIAL_SETUP_H_
#define _SERIAL_SETUP_H_

#include <Arduino.h>

#include "UI.h"
#include "Battery.h"
#include "Telemetry.h"
#include "types.h"

#define PROTOCOL_VERSION        0x00

#define GET_PROTOCOL_VERSION    0x00
#define GET_BATTERY_VOLTAGE     0x01
#define LOAD_FROM_EEPROM        0x02
#define SAVE_TO_EEPROM          0x03
#define DOWNLOAD                0x04
#define UPLOAD                  0x05
#define DOWNLOAD_TELEMETRY      0x06

#define TIMEOUT                 2500

class SerialSetup {

  public:

    SerialSetup(Setup * _setup, UI * _ui, Battery * _battery, Telemetry * _telemetry) : 
      setup(_setup), ui(_ui), battery(_battery), telemetry(_telemetry) {
      
      // Initialization
      init();
    
    }

    void handleSerialSetup();

  private:

    Setup * setup;
    UI * ui;
    Battery * battery;
    Telemetry * telemetry;

    void init();

    bool readCmd(uint8_t * cmd);
  
    bool executeGetProtocolVersion();

    bool executeGetBatteryVoltage();

    bool executeSaveToEEPROM();

    bool executeLoadFromEEPROM();

    bool executeDownload();

    bool executeUpload();

    bool executeDownloadTelemetry();

    void writeData(const void * data, const uint16_t size);

    bool readData(const void * data, const uint16_t size, const uint32_t timeout = TIMEOUT);

    bool waitForData(const uint16_t count, const uint32_t timeout = TIMEOUT);
  
};

#endif
