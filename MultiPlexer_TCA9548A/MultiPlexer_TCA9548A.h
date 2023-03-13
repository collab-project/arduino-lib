/*  Copyright (c) 2021-2023, Collab
 *  All rights reserved
*/
/*
  MultiPlexer_TCA9548A.h - Control TCA9548A I2C multiplexer.
*/
#ifndef MultiPlexer_TCA9548A_h
#define MultiPlexer_TCA9548A_h

#include <Arduino.h>
#include <Wire.h>
#include <TCA9548A.h>
#include <ArduinoLog.h>

class MultiPlexer_TCA9548A
{
  public:
    MultiPlexer_TCA9548A(int i2c_addr = 0x70);
    void begin();
    void scan(bool ignoreMultiplexer = true);
    void scanAll();
    void closeAll();
    void openChannel(uint8_t channel_nr);
    void closeChannel(uint8_t channel_nr);
    void switchChannel(uint8_t channel_nr);

  private:
    TCA9548A* _mux;
    int _address;
};

#endif
