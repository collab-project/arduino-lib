/*  Copyright (c) 2020-2021, Collab
 *  All rights reserved
*/

#include <MultiPlexer_PCF8574.h>

MultiPlexer_PCF8574::MultiPlexer_PCF8574(uint8_t address, uint8_t sda, uint8_t scl) {
  _expander = new PCF8574(address, sda, scl);
}

void MultiPlexer_PCF8574::begin() {
  if (!_expander->begin()) {
    Serial.println("PCF8574 Error!");
  }
}

void MultiPlexer_PCF8574::loop() {
}

void MultiPlexer_PCF8574::pinMode(uint8_t pin, uint8_t mode, uint8_t initialValue) {
  _expander->pinMode(pin, mode, initialValue);
}

void MultiPlexer_PCF8574::digitalWrite(uint8_t pin, uint8_t value) {
  _expander->digitalWrite(pin, value);
}

uint8_t MultiPlexer_PCF8574::digitalRead(uint8_t pin, bool forceReadNow) {
  return _expander->digitalRead(pin, forceReadNow);
}
