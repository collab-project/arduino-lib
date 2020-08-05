/*
  Potentiometer_ADS1115.cpp - Control potentiometer using ADS1115.
*/

#include "Potentiometer_ADS1115.h"

Potentiometer_ADS1115::Potentiometer_ADS1115(
    int channel,
    MultiPlexer_ADS1115* adc,
    Method callback
) {
  _channel = channel;
  _adc = adc;
  _callback = callback;
}

void Potentiometer_ADS1115::begin() {
}

void Potentiometer_ADS1115::loop() {
  read();
}

void Potentiometer_ADS1115::read() {
  if (_channel == 0) {
    _val = _adc->readChannel0();
  } else if (_channel == 1) {
    _val = _adc->readChannel1();
  } else if (_channel == 2) {
    _val = _adc->readChannel2();
  } else if (_channel == 3) {
    _val = _adc->readChannel3();
  }
  if (_val != _prev) {
    _prev = _val;
    _callback.callbackIntArg(_val);
  }
}
