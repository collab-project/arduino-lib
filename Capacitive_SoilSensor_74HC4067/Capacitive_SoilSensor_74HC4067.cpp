/*
  Capacitive_SoilSensor_74HC4067.cpp - Read Capacitive Soil Moisture Sensor using 74HC4067 multiplexer.
*/
#include "Capacitive_SoilSensor_74HC4067.h"

Capacitive_SoilSensor_74HC4067::Capacitive_SoilSensor_74HC4067(byte channel, int wet, int dry)
{
  _channel = channel;
  _wet = wet;
  _dry = dry;
}

int Capacitive_SoilSensor_74HC4067::measure(MultiPlexer_74HC4067* mux) {
  return mux->read(_channel);
}

int Capacitive_SoilSensor_74HC4067::measurePercentage(MultiPlexer_74HC4067* mux) {
  // read the input
  int data = measure(mux);

  // map to percentage
  return _max(map(data, _wet, _dry, 100, 0), 0);
}
