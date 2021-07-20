/*  Copyright (c) 2020-2021, Collab
 *  All rights reserved
*/
/*
  Button.cpp - Control button.
*/

#include "Button.h"

Button::Button(int btn_pin, int pin_mode, int last_state, int active_state) {
  _btnPin = btn_pin;
  _pinMode = pin_mode;
  _lastBtnState = last_state;
  _activeState = active_state;
}

void Button::begin(Method callback) {
  pinMode(_btnPin, _pinMode);

  _callback = callback;
}

void Button::loop() {
  read();
}

void Button::read() {
  int val = digitalRead(_btnPin);

  // if the switch changed, due to noise or pressing
  if (val != _lastBtnState) {
    // reset the debouncing timer
    _lastDebounceTime = millis();

  }
  if ((millis() - _lastDebounceTime) > _debounceDelay) {
    // if the button state has changed
    if (val != _currentBtnState) {
      _currentBtnState = val;

      if (_currentBtnState == _activeState) {
        _callback.callback();
      }
    }
  }
  // save the switch reading
  _lastBtnState = val;
}