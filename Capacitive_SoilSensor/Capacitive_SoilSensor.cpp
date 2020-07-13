/*
  Capacitive_SoilSensor.cpp - Read Capacitive Soil Moisture Sensor.
*/
#include "Capacitive_SoilSensor.h"

Capacitive_SoilSensor::Capacitive_SoilSensor(int pin, int wet, int dry) {
  _pin = pin;
  _wet = wet;
  _dry = dry;
}

void Capacitive_SoilSensor::begin() {
  pinMode(_pin, INPUT);
}

int Capacitive_SoilSensor::measure() {
  return analogRead(_pin);
}

int Capacitive_SoilSensor::measurePercentage() {
  // read the input
  int data = measure();

  // map to percentage
  return _max(map(data, _wet, _dry, 100, 0), 0);
}
