/*
  Capacitive_SoilSensor_Mux.h - Read Capacitive Soil Moisture Sensor using multiplexer.
*/
#ifndef Capacitive_SoilSensor_Mux_h
#define Capacitive_SoilSensor_Mux_h

#include "Arduino.h"
#include <MultiPlexer_74HC4067.h>

class Capacitive_SoilSensor_Mux
{
  public:
    Capacitive_SoilSensor_Mux(byte channel, int wet, int dry);
    int measure(MultiPlexer_74HC4067* mux);
    int measurePercentage(MultiPlexer_74HC4067* mux);

  private:
    byte _channel;
    int _wet;
    int _dry;
};

#endif