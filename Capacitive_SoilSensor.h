/*
  Capacitive_SoilSensor.h - Read Capacitive Soil Moisture Sensor.
*/
#ifndef Capacitive_SoilSensor_h
#define Capacitive_SoilSensor_h

#include "Arduino.h"
#include <MultiPlexer_74HC4067.h>

class Capacitive_SoilSensor
{
  public:
    Capacitive_SoilSensor(byte channel, int wet, int dry);
    int measure(MultiPlexer_74HC4067* mux);
    int measurePercentage(MultiPlexer_74HC4067* mux);

  private:
    byte _channel;
    int _wet;
    int _dry;
};

#endif