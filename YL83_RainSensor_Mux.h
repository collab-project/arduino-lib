/*
  YL83_RainSensor_Mux.h - Control YL-83 rain sensor using a multiplexer.
*/
#ifndef YL83_RainSensor_Mux_h
#define YL83_RainSensor_Mux_h

#include "Arduino.h"
#include <MultiPlexer_74HC4067.h>

class YL83_RainSensor_Mux
{
  public:
    YL83_RainSensor_Mux() {};
    YL83_RainSensor_Mux(int rain_pin);
    void begin();
    int measure(MultiPlexer_74HC4067* mux);
    int measurePercentage(MultiPlexer_74HC4067* mux);

  private:
    int _rainPin;
};

#endif