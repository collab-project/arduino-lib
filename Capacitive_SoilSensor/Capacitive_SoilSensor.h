/*
  Capacitive_SoilSensor_Mux.h - Read Capacitive Soil Moisture Sensor.
*/
#ifndef Capacitive_SoilSensor_h
#define Capacitive_SoilSensor_h

#include "Arduino.h"

class Capacitive_SoilSensor
{
  public:
    Capacitive_SoilSensor(int pin, int wet, int dry);
    void begin();
    int measure();
    int measurePercentage();

  private:
    int _pin;
    int _wet;
    int _dry;
};

#endif