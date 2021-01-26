/*  Copyright (c) 2020-2021, Collab
 *  All rights reserved
*/

#include "WaterFloatSwitch_PCF8574.h"

WaterFloatSwitch_PCF8574::WaterFloatSwitch_PCF8574(
  int switch_pin,
  MultiPlexer_PCF8574* pcf
) {
  _switchPin = switch_pin;
  _expander = pcf;
}

void WaterFloatSwitch_PCF8574::begin() {
  _expander->pinMode(_switchPin, INPUT);
}

uint8_t WaterFloatSwitch_PCF8574::read() {
  int result = _expander->digitalRead(_switchPin);

  if (result == HIGH) {
    if (_lastState != HIGH) {
      Serial.print(millis());
      Serial.println(" - Float switch HIGH");

      _empty = false;
    }
  } else if (result == LOW) {
      if (_lastState != LOW) {
        Serial.print(millis());
        Serial.println(" - Float switch LOW");

        _empty = true;
      }
  }
  _lastState = result;
  return result;
}

bool WaterFloatSwitch_PCF8574::isEmpty() {
  read();
  return _empty;
}
