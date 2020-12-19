/*  Copyright (c) 2020, Collab
 *  All rights reserved
*/
/*
  Button.cpp - Control button.
*/

#include "Button.h"

Button::Button(int btn_pin, int pin_mode) {
  _btnPin = btn_pin;
  _pinMode = pin_mode;
  _lastBtnState = LOW;
}

void Button::begin(Method callback) {
  pinMode(_btnPin, _pinMode);
  digitalWrite(_btnPin, _lastBtnState);

  _callback = callback;
}

void Button::loop() {
  read();
}

void Button::read() {
  int powerButtonReading = digitalRead(_btnPin);

  // if the switch changed, due to noise or pressing
  if (powerButtonReading != _lastBtnState) {
    // reset the debouncing timer
    _lastDebounceTime = millis();
  }
  if ((millis() - _lastDebounceTime) > _debounceDelay) {
    // if the button state has changed
    if (powerButtonReading != _currentBtnState) {
      _currentBtnState = powerButtonReading;

      // only toggle if the new button state is HIGH
      if (_currentBtnState == HIGH) {
        _callback.callback();
      }
    }
  }
  // save the switch reading
  _lastBtnState = powerButtonReading;
}