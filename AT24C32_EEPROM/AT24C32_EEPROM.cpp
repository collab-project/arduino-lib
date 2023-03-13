/*  Copyright (c) 2021-2023, Collab
 *  All rights reserved
*/
#include "AT24C32_EEPROM.h"

AT24C32_EEPROM::AT24C32_EEPROM(uint8_t eeprom_address, TwoWire* wire) {
  _eepromAddress = eeprom_address;
  _wire = wire;
}

void AT24C32_EEPROM::write_byte(unsigned int eeaddress, byte data) {
  int rdata = data;
  _wire->beginTransmission(_eepromAddress);
  _wire->write((int)(eeaddress >> 8)); // MSB
  _wire->write((int)(eeaddress & 0xFF)); // LSB
  _wire->write(rdata);
  _wire->endTransmission();
}

void AT24C32_EEPROM::write_page(unsigned int eeaddresspage, byte* data, byte length) {
  _wire->beginTransmission(_eepromAddress);
  _wire->write((int)(eeaddresspage >> 8)); // MSB
  _wire->write((int)(eeaddresspage & 0xFF)); // LSB
  byte c;
  for (c = 0; c < length; c++) {
    _wire->write(data[c]);
  }
  _wire->endTransmission();
}

byte AT24C32_EEPROM::read_byte(unsigned int eeaddress) {
  byte rdata = 0xFF;
  _wire->beginTransmission(_eepromAddress);
  _wire->write((int)(eeaddress >> 8)); // MSB
  _wire->write((int)(eeaddress & 0xFF)); // LSB
  _wire->endTransmission();
  _wire->requestFrom(_eepromAddress, 1);
  if (_wire->available()) {
    rdata = _wire->read();
  }
  return rdata;
}

void AT24C32_EEPROM::read_buffer(unsigned int eeaddress, byte *buffer, int length) {
  _wire->beginTransmission(_eepromAddress);
  _wire->write((int)(eeaddress >> 8)); // MSB
  _wire->write((int)(eeaddress & 0xFF)); // LSB
  _wire->endTransmission();
  _wire->requestFrom(_eepromAddress, length);
  int c = 0;
  for (c = 0; c < length; c++) {
    if (_wire->available()) {
      buffer[c] = _wire->read();
    }
  }
}
