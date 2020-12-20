/*  Copyright (c) 2020, Collab
 *  All rights reserved
*/
/*
  Button_PCF8574.cpp - Control PCF8574 connected button.
*/

#include "Button_PCF8574.h"

Button_PCF8574::Button_PCF8574(
    int btn_pin,
    MultiPlexer_PCF8574* pcf,
    Method callback
) {
  _btnPin = btn_pin;
  _expander = pcf;
  _callback = callback;
  _lastBtnState = LOW;
}

void Button_PCF8574::begin() {
  _expander->pinMode(_btnPin, INPUT);
}

void Button_PCF8574::loop() {
  read();
}

void Button_PCF8574::read() {
  /*
  int buttonReading = _mcp->getPin(_btnPin, _port);

  // if the switch changed, due to noise or pressing
  if (buttonReading != _lastBtnState) {
    // reset the debouncing timer
    _lastDebounceTime = millis();
  }
  if ((millis() - _lastDebounceTime) > _debounceDelay) {
    // if the button state has changed
    if (buttonReading != _currentBtnState) {
      _currentBtnState = buttonReading;

      // only toggle if the new button state is HIGH
      if (_currentBtnState == HIGH) {
        _callback.callbackIntArg(_btnPin);
      }
    }
  }
  // save the switch reading
  _lastBtnState = buttonReading;
  */
}