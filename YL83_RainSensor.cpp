/*
  YL83_RainSensor.cpp - Control YL-83 rain sensor.
*/
#include "YL83_RainSensor.h"

YL83_RainSensor::YL83_RainSensor(int rain_pin) {
  _rainPin = rain_pin;
}

void YL83_RainSensor::begin() {
  pinMode(_rainPin, INPUT);
}

void YL83_RainSensor::loop() {
}

int YL83_RainSensor::measure() {
  return analogRead(_rainPin);
}

int YL83_RainSensor::measurePercentage() {
  // read the input
  int output_value = measure();

  // map to percentage
  return map(output_value, 0, 4095, 100, 0);
}

bool YL83_RainSensor::wet() {
  int sensorValue = measure();
  return sensorValue < _thresholdValue;
}