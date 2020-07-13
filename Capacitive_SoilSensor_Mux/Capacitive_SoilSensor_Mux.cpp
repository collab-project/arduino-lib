/*
  Capacitive_SoilSensor_Mux.cpp - Read Capacitive Soil Moisture Sensor using multiplexer.
*/
#include "Capacitive_SoilSensor_Mux.h"

Capacitive_SoilSensor_Mux::Capacitive_SoilSensor_Mux(byte channel, int wet, int dry) {
  _channel = channel;
  _wet = wet;
  _dry = dry;
}

int Capacitive_SoilSensor_Mux::measure(MultiPlexer_74HC4067* mux) {
  return mux->read(_channel);
}

int Capacitive_SoilSensor_Mux::measurePercentage(MultiPlexer_74HC4067* mux) {
  // read the input
  int data = measure(mux);

  // map to percentage
  return _max(map(data, _wet, _dry, 100, 0), 0);
}
