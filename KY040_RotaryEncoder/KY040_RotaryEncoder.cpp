/*  Copyright (c) 2020, Collab
 *  All rights reserved
*/
/*
  KY040_RotaryEncoder.cpp - KY-040 rotary encoder with push button.
*/

#include "KY040_RotaryEncoder.h"

// declared here so timeIRS() below can access it
ClickEncoder* _encoder;

void timeIRS() {
  _encoder->service();
}

KY040_RotaryEncoder::KY040_RotaryEncoder(
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
}

void KY040_RotaryEncoder::begin() {
  _encoder = new ClickEncoder(_pinA, _pinB, _btnPin, 2);
  _encoder->setAccelerationEnabled(false);

  Timer1.initialize(1000);
  Timer1.attachInterrupt(timeIRS);

  _last = _encoder->getValue();
}

int16_t KY040_RotaryEncoder::getValue() {
  return _last;
}

void KY040_RotaryEncoder::loop() {
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
      case ClickEncoder::Pressed:
      case ClickEncoder::Clicked:
        _btnPressCallback.callback();
        break;
      case ClickEncoder::DoubleClicked:
        Serial.println("ClickEncoder::DoubleClicked");
        _encoder->setAccelerationEnabled(!_encoder->getAccelerationEnabled());
        Serial.print("  Acceleration is ");
        Serial.println((_encoder->getAccelerationEnabled()) ? "enabled" : "disabled");
        break;
    }
  }
}
