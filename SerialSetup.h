#ifndef _SERIAL_SETUP_H_
#define _SERIAL_SETUP_H_

#include <Arduino.h>

#include "settings.h"
#include "UI.h"
#include "Battery.h"

#define PROTOCOL_VERSION        0x00

#define GET_PROTOCOL_VERSION    0x00
#define GET_BATTERY_VOLTAGE     0x01
#define LOAD_FROM_EEPROM        0x02
#define SAVE_TO_EEPROM          0x03
#define DOWNLOAD                0x04
#define UPLOAD                  0x05

#define TIMEOUT                 2500

class SerialSetup {

  public:

    SerialSetup(Settings * _settings, UI * _ui, Battery * _battery) : settings(_settings), ui(_ui), battery(_battery) {
      
      // Initialization
      init();
    
    };

    void handleSerialSetup();

  private:

    Settings * settings;
    UI * ui;
    Battery * battery;

    void init();

    bool readCmd(byte * cmd);
  
    bool executeGetProtocolVersion();

    bool executeGetBatteryVoltage();

    bool executeSaveToEEPROM();

    bool executeLoadFromEEPROM();

    bool executeDownload();

    bool executeUpload();

    void writeByte(const byte data);

    void writeInt(const unsigned int data);

    bool readByte(byte * data, const unsigned long timeout = TIMEOUT);

    bool readInt(unsigned int * data, const unsigned long timeout = TIMEOUT);

    bool waitForData(const unsigned int count, const unsigned long timeout = TIMEOUT);
  
};

#endif
