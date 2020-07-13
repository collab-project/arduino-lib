/*
  YL83_RainSensor.h - Control YL-83 rain sensor.
*/
#ifndef YL83_RainSensor_h
#define YL83_RainSensor_h

#include "Arduino.h"

class YL83_RainSensor
{
  public:
    YL83_RainSensor() {};
    YL83_RainSensor(int rain_pin);
    void begin();
    void loop();
    int measure();
    int measurePercentage();

  private:
    int _rainPin;
};

#endif