/*
  YL83_RainSensor_Mux.cpp - Control YL-83 rain sensor using a multiplexer.
*/
#include "YL83_RainSensor_Mux.h"

YL83_RainSensor_Mux::YL83_RainSensor_Mux(int rain_pin) {
  _rainPin = rain_pin;
}

void YL83_RainSensor_Mux::begin() {
}

int YL83_RainSensor_Mux::measure(MultiPlexer_74HC4067* mux) {
  return mux->read(_rainPin);
}

int YL83_RainSensor_Mux::measurePercentage(MultiPlexer_74HC4067* mux) {
  // read the input
  int output_value = measure(mux);

  // map to percentage
  return map(output_value, 0, 4095, 100, 0);
}
