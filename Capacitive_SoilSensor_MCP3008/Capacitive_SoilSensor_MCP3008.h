/*  Copyright (c) 2020-2021, Collab
 *  All rights reserved
*/
/*
  Capacitive_SoilSensor.h - Read Capacitive Soil Moisture Sensor using MCP3008.
*/
#ifndef Capacitive_SoilSensor_MCP3008_h
#define Capacitive_SoilSensor_MCP3008_h

#include <Arduino.h>

class Capacitive_SoilSensor_MCP3008 {
  public:
    Capacitive_SoilSensor_MCP3008(int pin, int wet, int dry);
    void begin();
    int measure();
    int measurePercentage();

  private:
    int _pin;
    int _wet;
    int _dry;
};

#endif