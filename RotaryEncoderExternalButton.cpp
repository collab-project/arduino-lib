/*
  RotaryEncoderExternalButton.cpp - Rotary encoder with external push button.
*/

#include "RotaryEncoderExternalButton.h"

ClickEncoder* _encoder;

void timeISR() {
  _encoder->service();
}

RotaryEncoderExternalButton::RotaryEncoderExternalButton(
    int a_pin,
    int b_pin,
    int btn_pin,
    int stepsPerNotch,
    Method btn_callback,
    Method encoder_callback
) {
  _pinA = a_pin;
  _pinB = b_pin;
  _btnPin = btn_pin;
  _stepsPerNotch = stepsPerNotch;
  _btnCallback = btn_callback;
  _encoderCallback = encoder_callback;

  _btn = new Button(btn_pin);
}

void RotaryEncoderExternalButton::begin() {
  _encoder = new ClickEncoder(_pinA, _pinB, _btnPin, _stepsPerNotch);

  Timer1.initialize(1000);
  Timer1.attachInterrupt(timeISR);
  
  _last = 0;

  // btn
  _btn->begin(_btnCallback);
}

void RotaryEncoderExternalButton::loop() {
  _btn->loop();

  _value += _encoder->getValue();
  if (_value != _last) {
    _last = _value;
    _encoderCallback.callback();
  }
}

int16_t RotaryEncoderExternalButton::getValue() {
  return _last; 
}
