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
        MultiPlexer_TCA9548A* i2c,
        int scl_pin,
        int sda_pin,
        int address = 0x23,
        int bus_nr = 0,
        int clock_speed = 100000);
    void begin();
    float read();

  private:
    BH1750* _lightMeter;
    TwoWire* _i2c;
    int _sclPin;
    int _sdaPin;
    int _address;
    int _busNr;
    int _clockSpeed;
};

#endif