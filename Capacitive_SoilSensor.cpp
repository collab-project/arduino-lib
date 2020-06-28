/*
  Capacitive_SoilSensor.cpp - Read Capacitive Soil Moisture Sensor.
*/
#include "Capacitive_SoilSensor.h"

Capacitive_SoilSensor::Capacitive_SoilSensor(byte channel, int wet, int dry) {
  _channel = channel;
  _wet = wet;
  _dry = dry;
}

int Capacitive_SoilSensor::measure(MultiPlexer_74HC4067* mux) {
  return mux->read(_channel);
}

int Capacitive_SoilSensor::measurePercentage(MultiPlexer_74HC4067* mux) {
  // read the input
  int data = measure(mux);

  // map to percentage
  return _max(map(data, _wet, _dry, 100, 0), 0);
}
