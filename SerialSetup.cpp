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

  // Write protocol version
  writeByte((unsigned byte) PROTOCOL_VERSION);

  return true;
  
}

bool SerialSetup::executeGetBatteryVoltage() {

  // Read battery volts
  float volts;
  battery->readVoltage(& volts);

  // Convert to millivolts
  unsigned int millivolts = (unsigned int) (volts * 1000);

  // Write millivolt
  writeInt(millivolts);

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
  writeInt(settings->pidProportional);
  writeInt(settings->pidIntegrative);
  writeInt(settings->pidDerivative);
  writeInt(settings->motorsMaxSpeed);
  writeInt(settings->irInLineThreshold);
  writeInt(settings->irNoiseThreshold);

  return true;
  
}

bool SerialSetup::executeUpload() {

  bool result = true;
  
  // Read data
  result = result && readInt(& settings->pidProportional);
  result = result && readInt(& settings->pidIntegrative);
  result = result && readInt(& settings->pidDerivative);
  result = result && readInt(& settings->motorsMaxSpeed);
  result = result && readInt(& settings->irInLineThreshold);
  result = result && readInt(& settings->irNoiseThreshold);

  return result;
  
}

void SerialSetup::writeByte(const byte data) {

  // Write data
  Serial.write(data);
  
}

void SerialSetup::writeInt(const unsigned int data) {

  // Write data
  Serial.write((byte) (data >> 8));
  Serial.write((byte) data);
  
}

bool SerialSetup::readByte(byte * data, const unsigned long timeout = TIMEOUT) {

  bool dataAvailable = waitForData(1);

  if (dataAvailable) {

    // Read data
    * data = Serial.read();
    
  }

  return dataAvailable;
  
}

bool SerialSetup::readInt(unsigned int * data, const unsigned long timeout = TIMEOUT) {

  bool dataAvailable = waitForData(2);

  if (dataAvailable) {

    // Read data
    * data = Serial.read();
    * data <<= 8;
    * data += Serial.read();
    
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

