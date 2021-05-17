/*  Copyright (c) 2020-2021, Collab
 *  All rights reserved
*/
/*
  BH1750_LightSensor_Mux.h - Read BH1750 light sensor using a TCA9548A I2C expander.
*/
#ifndef BH1750_LightSensor_Mux_h
#define BH1750_LightSensor_Mux_h

#include <Arduino.h>
#include <Wire.h>
#include <BH1750.h>
#include <MultiPlexer_TCA9548A.h>

class BH1750_LightSensor_Mux {
  public:
    BH1750_LightSensor_Mux(
      MultiPlexer_TCA9548A* expander,
      uint8_t expander_channel,
      int address = 0x23,
      BH1750::Mode modus = BH1750::Mode::CONTINUOUS_HIGH_RES_MODE
    );
    void begin();
    float read();

  private:
    int _address;
    BH1750* _lightMeter;
    BH1750::Mode _modus;
    uint8_t _expanderChannel;
    MultiPlexer_TCA9548A* _expander;
};

#endif