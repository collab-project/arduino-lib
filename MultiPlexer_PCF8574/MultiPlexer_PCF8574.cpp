/*  Copyright (c) 2020-2021, Collab
 *  All rights reserved
*/

#include <MultiPlexer_PCF8574.h>

MultiPlexer_PCF8574::MultiPlexer_PCF8574(uint8_t address, uint8_t sda, uint8_t scl) {
  _sdaPin = sda;
  _sclPin = scl;
  _expander = new PCF8574(address);
}

void MultiPlexer_PCF8574::begin() {
  _expander->begin(_sdaPin, _sclPin);
}

void MultiPlexer_PCF8574::digitalWrite(uint8_t pin, uint8_t value) {
  _expander->write(pin, value);
}

uint8_t MultiPlexer_PCF8574::digitalRead(uint8_t pin) {
  return _expander->read(pin);
}
