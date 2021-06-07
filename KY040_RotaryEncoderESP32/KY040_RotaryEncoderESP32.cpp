/*  Copyright (c) 2020-2021, Collab
 *  All rights reserved
*/
/*
  KY040_RotaryEncoderESP32.cpp - ESP32 version of KY-040 rotary encoder with push button.
*/

#include "KY040_RotaryEncoderESP32.h"

KY040_RotaryEncoderESP32::KY040_RotaryEncoderESP32(
    int a_pin,
    int b_pin,
    int btn_pin,
    Method btnPress_callback,
    Method encoder_callback
) {
  _pinA = a_pin;
  _pinB = b_pin;
  _btnPin = btn_pin;
  _btnPressCallback = btnPress_callback;
  _encoderCallback = encoder_callback;

  _encoder = new ESP32Encoder();
  _btn = new Button(_btnPin, INPUT_PULLUP);
}

void KY040_RotaryEncoderESP32::begin() {
  // encoder
  _encoder->attachHalfQuad(_pinA, _pinB);
  _position = _encoder->getCount();

  // button
  _btn->begin(_btnPressCallback);
}

void KY040_RotaryEncoderESP32::loop() {
  // encoder
  _value = _encoder->getCount();
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

  // button
  _btn->loop();
}
