/*  Copyright (c) 2021, Collab
 *  All rights reserved
*/
#include "AT24C32_EEPROM.h"

AT24C32_EEPROM::AT24C32_EEPROM(uint8_t eeprom_address) {
  _eepromAddress = eeprom_address;
}

void AT24C32_EEPROM::write_byte(unsigned int eeaddress, byte data) {
  int rdata = data;
  Wire.beginTransmission(_eepromAddress);
  Wire.write((int)(eeaddress >> 8)); // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.write(rdata);
  Wire.endTransmission();
}

void AT24C32_EEPROM::write_page(unsigned int eeaddresspage, byte* data, byte length) {
  Wire.beginTransmission(_eepromAddress);
  Wire.write((int)(eeaddresspage >> 8)); // MSB
  Wire.write((int)(eeaddresspage & 0xFF)); // LSB
  byte c;
  for (c = 0; c < length; c++) {
    Wire.write(data[c]);
  }
  Wire.endTransmission();
}

byte AT24C32_EEPROM::read_byte(unsigned int eeaddress) {
  byte rdata = 0xFF;
  Wire.beginTransmission(_eepromAddress);
  Wire.write((int)(eeaddress >> 8)); // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.endTransmission();
  Wire.requestFrom(_eepromAddress, 1);
  if (Wire.available()) {
    rdata = Wire.read();
  }
  return rdata;
}

void AT24C32_EEPROM::read_buffer(unsigned int eeaddress, byte *buffer, int length) {
  Wire.beginTransmission(_eepromAddress);
  Wire.write((int)(eeaddress >> 8)); // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.endTransmission();
  Wire.requestFrom(_eepromAddress, length);
  int c = 0;
  for (c = 0; c < length; c++) {
    if (Wire.available()) buffer[c] = Wire.read();
  }
}
