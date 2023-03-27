/*  Copyright (c) 2020-2023, Collab
 *  All rights reserved
*/
/*
  BH1750_LightSensor_Mux.h - Read BH1750 light sensor using a TCA9548A I2C expander.
*/
#ifndef BH1750_LightSensor_Mux_h
#define BH1750_LightSensor_Mux_h

#include <Arduino.h>
#include <Wire.h>
#include <BH1750_WE.h>
#include <MultiPlexer_TCA9548A.h>

class BH1750_LightSensor_Mux {
  public:
    BH1750_LightSensor_Mux(
      MultiPlexer_TCA9548A* expander,
      TwoWire* wire,
      uint8_t expander_channel,
      int address = 0x23,
      BH1750Mode modus = BH1750Mode::CHM
    );
    void begin();
    float read();

  private:
    int _address;
    BH1750Mode _modus;
    uint8_t _expanderChannel;

    BH1750_WE* _lightMeter;
    MultiPlexer_TCA9548A* _expander;
};

#endif