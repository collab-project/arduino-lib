/*
  FC28_SoilSensor.h - Read FC-28 soil moisture sensor.
*/
#ifndef FC28_SoilSensor_h
#define FC28_SoilSensor_h

#include "Arduino.h"

struct SoilMoistureResult {
    float array[2];
};

class FC28_SoilSensor
{
  public:
    FC28_SoilSensor() {};
    FC28_SoilSensor(int soil_pin);
    void begin();
    void loop();
    int measure();
    int measurePercentage();

  private:
    int _soilPin;
};

#endif