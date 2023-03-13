/*  Copyright (c) 2020-2023, Collab
 *  All rights reserved
*/

#include <MultiPlexer_PCF8574.h>

MultiPlexer_PCF8574::MultiPlexer_PCF8574(uint8_t address, TwoWire* wire) {
  _expander = new PCF8574(address, wire);
}

bool MultiPlexer_PCF8574::begin() {
  bool expanderReady = _expander->begin();
  if (!expanderReady) {
    Log.warning(F("PCF8574 could not initialize!" CR));
  }
  if (!isConnected()) {
    Log.warning(F("PCF8574 not connected!" CR));
  }
  return expanderReady;
}

bool MultiPlexer_PCF8574::isConnected() {
  return _expander->isConnected();
}

void MultiPlexer_PCF8574::digitalWrite(uint8_t pin, uint8_t value) {
  _expander->write(pin, value);
}

uint8_t MultiPlexer_PCF8574::digitalRead(uint8_t pin) {
  return _expander->read(pin);
}
