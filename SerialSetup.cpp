#include "SerialSetup.h"

void SerialSetup::handleSerialSetup() {

  byte cmd;

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

bool SerialSetup::readCmd(byte * cmd) {

  // Check if a byte is available
  if (Serial.available() > 0) {

    // Read command
    * cmd = (unsigned byte) Serial.read();

    return true;
    
  } else {
    return false;
  }
  
}
  
bool SerialSetup::executeGetProtocolVersion() {

  // Get version
  byte version = PROTOCOL_VERSION;

  // Write protocol version
  writeData(& version, 1);

  return true;
  
}

bool SerialSetup::executeGetBatteryVoltage() {

  // Read battery volts
  float volts;
  battery->readVoltage(& volts);

  // Convert to millivolts
  unsigned int millivolts = (unsigned int) (volts * 1000);

  // Write millivolt
  writeData(& millivolts, 2);

  return true;
  
}

bool SerialSetup::executeSaveToEEPROM() {

  // Write to EEPROM
  eeprom_write_block((const void *) settings, (void *) 0, sizeof(* settings));

  return true;
  
}

bool SerialSetup::executeLoadFromEEPROM() {

  // Read from EEPROM
  eeprom_read_block((void *) settings, (void *) 0, sizeof(* settings));

  return true;
  
}

bool SerialSetup::executeDownload() {

  // Write data
  writeData(settings, sizeof(Settings));
  
  return true;
  
}

bool SerialSetup::executeUpload() {

  // Read data
  bool result = readData(settings, sizeof(Settings));

  return result;
  
}

bool SerialSetup::executeDownloadTelemetry() {

  // Write data
  writeData(telemetry->data, sizeof(TelemetryData) * telemetry->size);

  return true;
  
}

void SerialSetup::writeData(const void * data, const unsigned int size) {

  // Get data pointer as byte pointer
  byte * pointer = (byte *) data;

  // Write to serial
  Serial.write(pointer, size);
  
}

bool SerialSetup::readData(const void * data, const unsigned int size, const unsigned long timeout = TIMEOUT) {

  // Wait for data available
  bool dataAvailable = waitForData(size);

  if (dataAvailable) {

    // Get data pointer as byte pointer
    byte * pointer = (byte *) data;

    // Read data
    Serial.readBytes(pointer, size);

  }

  return dataAvailable;
  
}

bool SerialSetup::waitForData(const unsigned int count, const unsigned long timeout = TIMEOUT) {

  // Get start time
  const unsigned long start = millis();
  
  // White for a byte
  while (Serial.available() < count) {

    if (millis() - start > timeout) {

      // Timeout expired
      return false;
      
    }
    
  }

  return true;
  
}

