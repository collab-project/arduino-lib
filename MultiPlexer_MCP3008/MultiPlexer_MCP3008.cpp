/*
  MultiPlexer_MCP3008.cpp - Control MCP3008 8-channel 10-bit ADC.
*/

#include "MultiPlexer_MCP3008.h"

MultiPlexer_MCP3008::MultiPlexer_MCP3008(uint8_t cs_pin) {
    _csPin = cs_pin;
    _adc = new Adafruit_MCP3008();
}

void MultiPlexer_MCP3008::begin() {
    _adc->begin(_csPin);
}

int MultiPlexer_MCP3008::read(uint8_t channel) {
    return _adc->readADC(channel);
}
