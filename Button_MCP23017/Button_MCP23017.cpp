/*
  Button_MCP23017.cpp - Control MCP23017 connected button.
*/

#include "Button_MCP23017.h"

Button_MCP23017::Button_MCP23017(
    int btn_pin,
    MCP_PORT mcp_port,
    MultiPlexer_MCP23017* mcp,
    Method callback
) {
  _btnPin = btn_pin;
  _mcp = mcp;
  _port = mcp_port;
  _callback = callback;
  _lastBtnState = LOW;
}

void Button_MCP23017::begin() {
}

void Button_MCP23017::loop() {
  read();
}

void Button_MCP23017::read() {
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
}