/*
  SerialSetup.cpp
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

#include "SerialSetup.h"

void SerialSetup::handleSerialSetup() {

  uint8_t cmd;

  if (readCmd(& cmd)) {

    // Turn led off
    ui->ledOff();

    bool result = false;

    if (cmd == GET_PROTOCOL_VERSION) {

      // Exexcute
      result = executeGetProtocolVersion();
      
    } else if (cmd == GET_BATTERY_VOLTAGE) {

      // Exexcute
      result = executeGetBatteryVoltage();
      
    } else if (cmd == LOAD_FROM_EEPROM) {

      // Exexcute
      result = executeLoadFromEEPROM();
      
    } else if (cmd == SAVE_TO_EEPROM) {

      // Exexcute
      result = executeSaveToEEPROM();
      
    } else if (cmd == DOWNLOAD) {

      // Exexcute
      result = executeDownload();
      
    } else if (cmd == UPLOAD) {

      // Exexcute
      result = executeUpload();
      
    } else if (cmd == DOWNLOAD_TELEMETRY) {

      // Exexcute
      result = executeDownloadTelemetry();
      
    }

    if (!result) {

      // Led blink fast
      ui->ledBlinkFastFor(1000);
      
    }

    // Turn led on
    ui->ledOn();
    
  }
  
}

void SerialSetup::init() {

  // Load settings from EEPROM
  executeLoadFromEEPROM();
  
}

bool SerialSetup::readCmd(uint8_t * cmd) {

  // Check if a byte is available
  if (Serial.available() > 0) {

    // Read command
    * cmd = (uint8_t) Serial.read();

    return true;
    
  } else {
    return false;
  }
  
}
  
bool SerialSetup::executeGetProtocolVersion() {

  // Get version
  uint8_t version = PROTOCOL_VERSION;

  // Write protocol version
  writeData(& version, 1);

  return true;
  
}

bool SerialSetup::executeGetBatteryVoltage() {

  // Read battery volts
  float volts;
  battery->readVoltage(& volts);

  // Convert to millivolts
  uint16_t millivolts = (uint16_t) (volts * 1000);

  // Write millivolt
  writeData(& millivolts, 2);

  return true;
  
}

bool SerialSetup::executeSaveToEEPROM() {

  // Write to EEPROM
  eeprom_write_block((const void *) setup, (void *) 0, sizeof(* setup));

  return true;
  
}

bool SerialSetup::executeLoadFromEEPROM() {

  // Read from EEPROM
  eeprom_read_block((void *) setup, (void *) 0, sizeof(* setup));

  return true;
  
}

bool SerialSetup::executeDownload() {

  // Write data
  writeData(setup, sizeof(Setup));
  
  return true;
  
}

bool SerialSetup::executeUpload() {

  // Read data
  bool result = readData(setup, sizeof(Setup));

  return result;
  
}

bool SerialSetup::executeDownloadTelemetry() {

  // Write data
  writeData(telemetry->data, sizeof(TelemetryData) * telemetry->size);

  return true;
  
}

void SerialSetup::writeData(const void * data, const uint16_t size) {

  // Get data pointer as byte pointer
  uint8_t * pointer = (uint8_t *) data;

  // Write to serial
  Serial.write(pointer, size);
  
}

bool SerialSetup::readData(const void * data, const uint16_t size, const uint32_t timeout = TIMEOUT) {

  // Wait for data available
  bool dataAvailable = waitForData(size);

  if (dataAvailable) {

    // Get data pointer as byte pointer
    uint8_t * pointer = (uint8_t *) data;

    // Read data
    Serial.readBytes(pointer, size);

  }

  return dataAvailable;
  
}

bool SerialSetup::waitForData(const uint16_t count, const uint32_t timeout = TIMEOUT) {

  // Get start time
  const uint32_t start = millis();
  
  // White for a byte
  while (Serial.available() < count) {

    if (millis() - start > timeout) {

      // Timeout expired
      return false;
      
    }
    
  }

  return true;
  
}

