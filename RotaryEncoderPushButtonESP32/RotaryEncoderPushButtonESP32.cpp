/*
  RotaryEncoderPushButtonESP32.cpp - ESP32 version of rotary encoder with internal push button.
*/

#include "RotaryEncoderPushButtonESP32.h"

// declared here so handler below can access
Method _btnPressCallback;
Method _btnReleaseCallback;

void handleButtonEvent(
  AceButton* button,
  uint8_t eventType,
  uint8_t buttonState
) {
  switch (eventType) {
    case AceButton::kEventPressed:
      // notify others
      _btnPressCallback.callbackIntArg(button->getId());
      break;
    case AceButton::kEventReleased:
      // notify others
      _btnReleaseCallback.callbackIntArg(button->getId());
      break;
  }
}

RotaryEncoderPushButtonESP32::RotaryEncoderPushButtonESP32(
    uint8_t index,
    int a_pin,
    int b_pin,
    int btn_pin,
    Method btnPress_callback,
    Method btnRelease_callback,
    Method encoder_callback
) {
  _pinA = a_pin;
  _pinB = b_pin;
  _btnPin = btn_pin;
  _btnPressCallback = btnPress_callback;
  _btnReleaseCallback = btnRelease_callback;
  _encoderCallback = encoder_callback;

  _encoder = new ESP32Encoder();
  _btnCfg = new ButtonConfig();
  _button = new AceButton(_btnCfg, _btnPin, HIGH, index);
}

void RotaryEncoderPushButtonESP32::begin() {
  // encoder
  _encoder->attachSingleEdge(_pinA, _pinB);

  // btn
  pinMode(_btnPin, INPUT_PULLUP);
  _btnCfg->setEventHandler(handleButtonEvent);
}

void RotaryEncoderPushButtonESP32::loop() {
  // button
  _button->check();

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
    _encoderCallback.callback();
  }
}

int64_t RotaryEncoderPushButtonESP32::getPosition() {
  return _encoder->getCount();
}
