/*
  Potentiometer_ADS1115.cpp - Control potentiometer using ADS1115.
*/

#include "Potentiometer_ADS1115.h"

Potentiometer_ADS1115::Potentiometer_ADS1115(
    int channel,
    int16_t max_voltage,
    int16_t range_min,
    int16_t range_max,
    MultiPlexer_ADS1115* adc,
    Method callback
) {
  _channel = channel;
  _maxVoltage = max_voltage;
  _rangeMin = range_min;
  _rangeMax = range_max;
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
    _val = _adc->readChannel0(_maxVoltage, _rangeMin, _rangeMax);
  } else if (_channel == 1) {
    _val = _adc->readChannel1(_maxVoltage, _rangeMin, _rangeMax);
  } else if (_channel == 2) {
    _val = _adc->readChannel2(_maxVoltage, _rangeMin, _rangeMax);
  } else if (_channel == 3) {
    _val = _adc->readChannel3(_maxVoltage, _rangeMin, _rangeMax);
  }
  if (_val != _prev) {
    _prev = _val;
    _callback.callbackIntArg(_val);
  }
}
