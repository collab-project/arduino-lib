/*  Copyright (c) 2020-2021, Collab
 *  All rights reserved
*/
/*
  YL83_RainSensor_MCP3008.h - Read YL-83 rain sensor using MCP3008.
*/
#ifndef YL83_RainSensor_MCP3008_h
#define YL83_RainSensor_MCP3008_h

#include <Arduino.h>
#include <MultiPlexer_MCP3008.h>

class YL83_RainSensor_MCP3008 {
  public:
    YL83_RainSensor_MCP3008(MultiPlexer_MCP3008* adc, int channel);
    void begin();
    int measure();
    int measurePercentage();

  private:
    int _channel;
    MultiPlexer_MCP3008 *_adc;
};

#endif