/*  Copyright (c) 2021, Collab
 *  All rights reserved
*/

#include "VibrationMotor_PCF8574.h"

VibrationMotor_PCF8574::VibrationMotor_PCF8574(
  int switch_pin,
  MultiPlexer_PCF8574* pcf,
  unsigned int period
) {
  _switchPin = switch_pin;
  _expander = pcf;
  _period = period;
}

void VibrationMotor_PCF8574::begin() {
  disable();
}

void VibrationMotor_PCF8574::loop() {
  if (_enabled) {
    if ((millis() - _enablePoint) >= _period) {
      disable();
    }
  }
}

void VibrationMotor_PCF8574::enable() {
  _enabled = true;
  _enablePoint = millis();

  _expander->digitalWrite(_switchPin, HIGH);
}

void VibrationMotor_PCF8574::disable() {
  _enabled = false;

  _expander->digitalWrite(_switchPin, LOW);
}
