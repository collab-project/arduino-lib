/*  Copyright (c) 2020-2021, Collab
 *  All rights reserved
*/
/*
  YL83_RainSensor_MCP3008.cpp - Read YL-83 rain sensor using MCP3008.
*/
#include <YL83_RainSensor_MCP3008.h>

YL83_RainSensor_MCP3008::YL83_RainSensor_MCP3008(MultiPlexer_MCP3008 *adc, int channel) {
  _adc = adc;
  _channel = channel;
}

void YL83_RainSensor_MCP3008::begin() {
}

int YL83_RainSensor_MCP3008::measure() {
  return _adc->read(_channel);
}

int YL83_RainSensor_MCP3008::measurePercentage() {
  // read the input
  int output_value = measure();

  // map to positive percentage
  return _max(map(output_value, 0, 4095, 100, 0), 0);
}
