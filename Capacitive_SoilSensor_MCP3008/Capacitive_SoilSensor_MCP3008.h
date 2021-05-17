/*  Copyright (c) 2020-2021, Collab
 *  All rights reserved
*/
/*
  Capacitive_SoilSensor.h - Read Capacitive Soil Moisture Sensor using MCP3008.
*/
#ifndef Capacitive_SoilSensor_MCP3008_h
#define Capacitive_SoilSensor_MCP3008_h

#include <Arduino.h>
#include <MultiPlexer_MCP3008.h>

class Capacitive_SoilSensor_MCP3008 {
  public:
    Capacitive_SoilSensor_MCP3008(
      MultiPlexer_MCP3008* adc,
      int channel,
      int wet,
      int dry
    );
    void begin();
    int measure();
    int measurePercentage();

  private:
    int _wet;
    int _dry;
    int _channel;
    MultiPlexer_MCP3008* _adc;
};

#endif