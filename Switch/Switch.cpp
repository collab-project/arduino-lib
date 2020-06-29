/*
  Switch.cpp - Control switch button.
*/

#include "Switch.h"

Switch::Switch(int switch_pin) {
  _switchPin = switch_pin;
}

void Switch::begin() {
  pinMode(_switchPin, INPUT_PULLUP);
  state = read();
}

int Switch::read() {
  return digitalRead(_switchPin);
}

void Switch::loop() {
  int reading = read();

  if (reading != state) {
    state = reading;
  }
}
