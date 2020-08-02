/*
  Potentiometer_ADS1115.cpp - Control potentiometer using ADS1115.
*/

#include "Potentiometer_ADS1115.h"

Potentiometer_ADS1115::Potentiometer_ADS1115(
    int pin,
    MultiPlexer_ADS1115* adc,
    Method callback
) {
  _pin = pin;
  _adc = adc;
  _callback = callback;
}

void Potentiometer_ADS1115::begin() {
}

void Potentiometer_ADS1115::loop() {
  read();
}

void Potentiometer_ADS1115::read() {
  if (_pin == 0) {
    _val = _adc->readChannel0();
  } else if (_pin == 1) {
    _val = _adc->readChannel1();
  } else if (_pin == 2) {
    _val = _adc->readChannel2();
  } else if (_pin == 3) {
    _val = _adc->readChannel3();
  }
  //_callback.callback();
}