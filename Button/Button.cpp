/*  Copyright (c) 2020-2021, Collab
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

      // only toggle if the new button state is HIGH
      if (_currentBtnState == HIGH) {
        _callback.callback();
      }
    }
  }
  // save the switch reading
  _lastBtnState = val;
}