/*  Copyright (c) 2022, Collab
 *  All rights reserved
*/

#include "VibrationMotor.h"

VibrationMotor::VibrationMotor(
  int motor_pin,
  unsigned int period
) {
  _motorPin = motor_pin;
  _period = period;
}

void VibrationMotor::begin() {
  pinMode(_motorPin, OUTPUT);
}

void VibrationMotor::loop() {
  if (_enabled) {
    if ((millis() - _enablePoint) >= _period) {
      disable();
    }
  }
}

void VibrationMotor::enable() {
  _enabled = true;
  _enablePoint = millis();

  digitalWrite(_motorPin, HIGH);
}

void VibrationMotor::disable() {
  _enabled = false;

  digitalWrite(_motorPin, LOW);
}
