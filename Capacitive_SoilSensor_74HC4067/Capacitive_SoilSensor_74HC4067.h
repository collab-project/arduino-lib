/*
  Capacitive_SoilSensor_74HC4067.h - Read Capacitive Soil Moisture Sensor using 74HC4067 multiplexer.
*/
#ifndef Capacitive_SoilSensor_74HC4067_h
#define Capacitive_SoilSensor_74HC4067_h

#include <Arduino.h>
#include <MultiPlexer_74HC4067.h>

class Capacitive_SoilSensor_74HC4067
{
  public:
    Capacitive_SoilSensor_74HC4067(byte channel, int wet, int dry);
    int measure(MultiPlexer_74HC4067* mux);
    int measurePercentage(MultiPlexer_74HC4067* mux);

  private:
    byte _channel;
    int _wet;
    int _dry;
};

#endif