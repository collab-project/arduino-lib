/*
  Capacitive_SoilSensor_MCP3008.cpp - Read Capacitive Soil Moisture Sensor using MCP3008.
*/
#include "Capacitive_SoilSensor_MCP3008.h"

Capacitive_SoilSensor_MCP3008::Capacitive_SoilSensor_MCP3008(int pin, int wet, int dry) {
  _pin = pin;
  _wet = wet;
  _dry = dry;
}

void Capacitive_SoilSensor_MCP3008::begin() {
  pinMode(_pin, INPUT);
}

int Capacitive_SoilSensor_MCP3008::measure() {
  return analogRead(_pin);
}

int Capacitive_SoilSensor_MCP3008::measurePercentage() {
  // read the input
  int data = measure();

  // map to percentage
  return _max(map(data, _wet, _dry, 100, 0), 0);
}
