/*  Copyright (c) 2020-2021, Collab
 *  All rights reserved
*/

#include "WaterFloatSwitch_PCF8574.h"

WaterFloatSwitch_PCF8574::WaterFloatSwitch_PCF8574(
  int switch_pin,
  MultiPlexer_PCF8574* pcf,
  int empty_value
) {
  _switchPin = switch_pin;
  _expander = pcf;
  _emptyValue = empty_value;
}

void WaterFloatSwitch_PCF8574::begin() {
}

uint8_t WaterFloatSwitch_PCF8574::read() {
  return _expander->digitalRead(_switchPin, false);
}

bool WaterFloatSwitch_PCF8574::isEmpty() {
  return (read() == _emptyValue);
}
