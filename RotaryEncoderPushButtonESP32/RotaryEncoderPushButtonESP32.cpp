/*
  RotaryEncoderPushButtonESP32.cpp - ESP32 version of rotary encoder with internal push button.
*/

#include "RotaryEncoderPushButtonESP32.h"

// declared here so functions below can access it
RotaryEncoder* _encoder;

void encoderISR()
{
  _encoder->readAB();
}

void encoderButtonISR()
{
  _encoder->readPushButton();
}

RotaryEncoderPushButtonESP32::RotaryEncoderPushButtonESP32(
    int a_pin,
    int b_pin,
    int btn_pin,
    Method btn_callback,
    Method encoder_callback
) {
  _pinA = a_pin;
  _pinB = b_pin;
  _btnPin = btn_pin;
  _btnCallback = btn_callback;
  _encoderCallback = encoder_callback;

  _encoder = new RotaryEncoder(_pinA, _pinB, _btnPin);
}

void RotaryEncoderPushButtonESP32::begin() {
  _encoder->begin();

  attachInterrupt(digitalPinToInterrupt(_pinA), encoderISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(_btnPin), encoderButtonISR, FALLING);

  _position = _encoder->getPosition();
}

void RotaryEncoderPushButtonESP32::loop() {
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
