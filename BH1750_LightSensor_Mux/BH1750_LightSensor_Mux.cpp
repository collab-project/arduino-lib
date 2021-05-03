/*  Copyright (c) 2020-2021, Collab
 *  All rights reserved
*/
/*
  BH1750_LightSensor_Mux.cpp - Read BH1750 light sensor using TCA9548A I2C expander.
*/
#include "BH1750_LightSensor_Mux.h"

BH1750_LightSensor_Mux::BH1750_LightSensor_Mux(
    MultiPlexer_TCA9548A* i2c,
    int scl_pin,
    int sda_pin,
    int address,
    int bus_nr,
    int clock_speed)
{
  _sclPin = scl_pin;
  _sdaPin = sda_pin;
  _address = address;
  _clockSpeed = clock_speed;
  _busNr = bus_nr;
}

void BH1750_LightSensor_Mux::begin() {
}

float BH1750_LightSensor_Mux::read() {
  // init I2C bus for every read!
  _i2c = new TwoWire(_busNr);
  _lightMeter = new BH1750();
  _i2c->begin(_sdaPin, _sclPin, _clockSpeed);

  // make sure all is good
  if (_lightMeter->begin(BH1750::CONTINUOUS_HIGH_RES_MODE, _address, _i2c)) {
    // Serial.println(F("BH1750 ready."));
  } else {
    Serial.println(F("Error initialising BH1750"));
  }

  float lux = _lightMeter->readLightLevel();
  if (lux == -1) {
    // try one more time
    lux = _lightMeter->readLightLevel();
  }
  return lux;
}
