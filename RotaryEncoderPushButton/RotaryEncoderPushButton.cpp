/*
  RotaryEncoderPushButton.cpp - Rotary encoder with internal push button.
*/

#include "RotaryEncoderPushButton.h"

// declared here so timeIRS() below can access it
ClickEncoder* _encoder;

void timeIRS() {
  _encoder->service();
}

RotaryEncoderPushButton::RotaryEncoderPushButton(
    int a_pin,
    int b_pin,
    int btn_pin,
    Method btnPress_callback,
    Method encoder_callback,
    int stepsPerNotch
) {
  _pinA = a_pin;
  _pinB = b_pin;
  _btnPin = btn_pin;
  _stepsPerNotch = stepsPerNotch;
  _btnPressCallback = btnPress_callback;
  _encoderCallback = encoder_callback;
}

void RotaryEncoderPushButton::begin() {
  _encoder = new ClickEncoder(_pinA, _pinB, _btnPin, _stepsPerNotch);
  _encoder->setAccelerationEnabled(false);

  Timer1.initialize(1000);
  Timer1.attachInterrupt(timeIRS);

  _last = _encoder->getValue();
}

int16_t RotaryEncoderPushButton::getValue() {
  return _last;
}

void RotaryEncoderPushButton::loop() {
  _value += _encoder->getValue();
  if (_value != _last) {

    if (_value > _last) {
      rotation = EventType::ROTARY_CCW;
    } else {
      rotation = EventType::ROTARY_CW;
    }
    _last = _value;

    // notify others
    _encoderCallback.callback();
  }

  ClickEncoder::Button b = _encoder->getButton();
  if (b != ClickEncoder::Open) {
    #define VERBOSECASE(label) case label: Serial.println(#label); break;
    switch (b) {
      VERBOSECASE(ClickEncoder::Held)
      VERBOSECASE(ClickEncoder::Released)
      VERBOSECASE(ClickEncoder::DoubleClicked)
      case ClickEncoder::Pressed:
      case ClickEncoder::Clicked:
        _btnPressCallback.callback();
        break;
    }
  }
}
