/*
  RCWL0516_MovementSensor.cpp - Control RCWL-0516 movement sensor.
*/

#include "RCWL0516_MovementSensor.h"

RCWL0516_MovementSensor::RCWL0516_MovementSensor(
  int sensor_pin,
  Method movementStart_callback,
  Method movementStop_callback
) {
  _sensorPin = sensor_pin;
  _movementStartCallback = movementStart_callback;
  _movementStopCallback = movementStop_callback;
}

void RCWL0516_MovementSensor::begin() {
  pinMode(_sensorPin, INPUT);
}

void RCWL0516_MovementSensor::loop() {
  if (enabled == true) {
    _value = digitalRead(_sensorPin);

    if (_value != _prevReading) {
      // notify others
      if (_value == HIGH) {
        _movementStartCallback.callback();
      } else {
        _movementStopCallback.callback();
      }
      _prevReading = _value;
    }
  }
}
