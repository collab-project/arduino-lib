/*  Copyright (c) 2020, Collab
 *  All rights reserved
*/
/*
  BH1750_LightSensor.h - Read BH1750 light sensor.
*/
#ifndef BH1750_LightSensor_h
#define BH1750_LightSensor_h

#include "Arduino.h"
#include <Wire.h>
#include <BH1750.h>

class BH1750_LightSensor
{
  public:
    BH1750_LightSensor() {};
    BH1750_LightSensor(
      int scl_pin,
      int sda_pin,
      int address = 0x23,
      int bus_nr = 0,
      int clock_speed = 100000
    );
    void begin();
    void loop();
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