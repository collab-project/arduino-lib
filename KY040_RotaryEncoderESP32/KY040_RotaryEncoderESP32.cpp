/*
  KY040_RotaryEncoderESP32.cpp - ESP32 version of KY-040 rotary encoder with push button.
*/

#include "KY040_RotaryEncoderESP32.h"

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

  _encoder = new RotaryEncoder(_pinA, _pinB, _btnPin);
}

void KY040_RotaryEncoderESP32::begin() {
  _encoder->begin();

  attachInterrupt(digitalPinToInterrupt(_pinA), encoderISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(_btnPin), encoderButtonISR, FALLING);

  _position = _encoder->getPosition();
}

void KY040_RotaryEncoderESP32::loop() {
  _value = _encoder->getPosition();
  if (_position != _value) {

    if (_position > _value) {
      rotation = EventType::ROTARY_CCW;
    } else {
      rotation = EventType::ROTARY_CW;
    }
    _position = _value;

    // notify others
    _encoderCallback.callback();
  }

  if (_encoder->getPushButton() == true) {
    _btnPressCallback.callback();
  }
}
