/*  Copyright (c) 2021, Collab
 *  All rights reserved
*/
#ifndef AT24C32_EEPROM_h
#define AT24C32_EEPROM_h

#include <Arduino.h>
#include <Wire.h>

class AT24C32_EEPROM
{
  public:
    AT24C32_EEPROM(uint8_t eeprom_address);
    byte read_byte(unsigned int eeaddress);
    void write_byte(unsigned int eeaddress, byte data);
    void write_page(unsigned int eeaddresspage, byte* data, byte length);
    void read_buffer(unsigned int eeaddress, byte *buffer, int length);

  private:
    uint8_t _eepromAddress;
};

#endif