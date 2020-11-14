/*
  RotaryEncoderMCP23017ButtonESP32.h - ESP32 version of rotary encoder with
  internal push button controlled by MCP23017 multiplexer.
*/

#include "RotaryEncoderMCP23017ButtonESP32.h"

RotaryEncoderMCP23017ButtonESP32::RotaryEncoderMCP23017ButtonESP32(
    uint8_t index,
    int a_pin,
    int b_pin,
    int btn_pin,
    Method btn_callback,
    Method encoder_callback,
    MultiPlexer_MCP23017* mcp,
    MCP_PORT port
) {
  _pinA = a_pin;
  _pinB = b_pin;
  _btnPin = btn_pin;
  _encoderCallback = encoder_callback;

  _encoder = new ESP32Encoder();
  _button = new Button_MCP23017(_btnPin, port, mcp, btn_callback);
}

void RotaryEncoderMCP23017ButtonESP32::begin() {
  // encoder
  _encoder->attachSingleEdge(_pinA, _pinB);

  // button
  _button->begin();
}

void RotaryEncoderMCP23017ButtonESP32::loop() {
  // button
  _button->loop();

  // encoder
  _value = getPosition();
  if (_position != _value) {
    if (_value > _position) {
      rotation = EventType::ROTARY_CW;
    } else {
      rotation = EventType::ROTARY_CCW;
    }
    _position = _value;

    // notify others
    _encoderCallback.callback2IntArg(_position, rotation);
  }
}

int64_t RotaryEncoderMCP23017ButtonESP32::getPosition() {
  return _encoder->getCount();
}
