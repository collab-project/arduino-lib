/*
  RotaryEncoderPushButtonESP32MCP23017.cpp - ESP32 MCP23017 version of rotary encoder with internal push button.
*/

#include "RotaryEncoderPushButtonESP32MCP23017.h"

// declared here so functions below can access it
RotaryEncoderMCP23017* _encoder;

void encoderISR()
{
  _encoder->readAB();
}

void encoderButtonISR()
{
  _encoder->readPushButton();
}

RotaryEncoderPushButtonESP32MCP23017::RotaryEncoderPushButtonESP32MCP23017(
    int a_pin,
    int b_pin,
    int btn_pin,
    Adafruit_MCP23017* mcp,
    Method btn_callback,
    Method encoder_callback
) {
  _pinA = a_pin;
  _pinB = b_pin;
  _btnPin = btn_pin;
  _btnCallback = btn_callback;
  _encoderCallback = encoder_callback;
  _mcp = mcp;

  _encoder = new RotaryEncoderMCP23017(_pinA, _pinB, _btnPin, mcp);
}

void RotaryEncoderPushButtonESP32MCP23017::begin() {
  _encoder->begin();

  _mcp->setupInterruptPin(_pinA, CHANGE);
  _mcp->setupInterruptPin(_btnPin, FALLING);

  // enable interrupts before going to sleep/wait
  // And we setup a callback for the arduino INT handler.
  attachInterrupt(digitalPinToInterrupt(_pinA), encoderISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(_btnPin), encoderButtonISR, FALLING);

  //attachInterrupt(digitalPinToInterrupt(_pinA), encoderISR, CHANGE);
  //attachInterrupt(digitalPinToInterrupt(_btnPin), encoderButtonISR, FALLING);

  _position = _encoder->getPosition();
}

void RotaryEncoderPushButtonESP32MCP23017::loop() {
  _value = _encoder->getPosition();
  if (_position != _value) {
    if (_value > _position) {
      rotation = EventType::ROTARY_CCW;
    } else {
      rotation = EventType::ROTARY_CW;
    }
    _position = _value;

    // notify others
    _encoderCallback.callback();
  }

  if (_encoder->getPushButton() == true) {
    _btnCallback.callback();
  }
}
