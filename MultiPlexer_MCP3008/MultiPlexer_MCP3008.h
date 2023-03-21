/*  Copyright (c) 2023, Collab
 *  All rights reserved
*/
/*
  MultiPlexer_MCP3008.h - Control MCP3008 8-channel 10-bit ADC.
*/
#ifndef MultiPlexer_MCP3008_h
#define MultiPlexer_MCP3008_h

#include <Arduino.h>
#include <Adafruit_MCP3008.h>

class MultiPlexer_MCP3008 {
    public:
        MultiPlexer_MCP3008(uint8_t cs_pin);
        void begin();
        int read(uint8_t channel);

    private:
        uint8_t _csPin;
        Adafruit_MCP3008 *_adc;
};

#endif
