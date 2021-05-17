/*
  Capacitive_SoilSensor_MCP3008.cpp - Read Capacitive Soil Moisture Sensor using MCP3008.
*/
#include "Capacitive_SoilSensor_MCP3008.h"

Capacitive_SoilSensor_MCP3008::Capacitive_SoilSensor_MCP3008(
  MultiPlexer_MCP3008* adc,
  int channel,
  int wet,
  int dry
) {
  _adc = adc;
  _channel = channel;
  _wet = wet;
  _dry = dry;
}

void Capacitive_SoilSensor_MCP3008::begin() {
}

int Capacitive_SoilSensor_MCP3008::measure() {
  return _adc->read(_channel);
}

int Capacitive_SoilSensor_MCP3008::measurePercentage() {
  // read the input
  int data = measure();

  // map to percentage
  return _max(map(data, _wet, _dry, 100, 0), 0);
}
