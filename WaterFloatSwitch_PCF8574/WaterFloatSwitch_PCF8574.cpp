/*  Copyright (c) 2020, Collab
 *  All rights reserved
*/

#include "WaterFloatSwitch_PCF8574.h"

WaterFloatSwitch_PCF8574::WaterFloatSwitch_PCF8574(
  int switch_pin,
  MultiPlexer_PCF8574* pcf,
  Method empty_callback
) {
  _switchPin = switch_pin;
  _expander = pcf;
  _emptyCallback = empty_callback;
}

void WaterFloatSwitch_PCF8574::begin() {
}

void WaterFloatSwitch_PCF8574::loop() {
}
