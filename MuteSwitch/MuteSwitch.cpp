/*  Copyright (c) 2021, Collab
 *  All rights reserved
*/

#include "MuteSwitch.h"

MuteSwitch::MuteSwitch(int pin, int switch_state) {
  _pin = pin;
  state = switch_state;
}

void MuteSwitch::begin() {
  pinMode(_pin, OUTPUT);
  update();
}

void MuteSwitch::loop() {
}

void MuteSwitch::update() {
  digitalWrite(_pin, state);
}

void MuteSwitch::enable() {
  state = LOW;
  update();
}

void MuteSwitch::disable() {
  state = HIGH;
  update();
}
