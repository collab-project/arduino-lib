/*  Copyright (c) 2020-2021, Collab
 *  All rights reserved
*/
/*
  BH1750_LightSensor_Mux.cpp - Read BH1750 light sensor using TCA9548A I2C expander.
*/
#include "BH1750_LightSensor_Mux.h"

BH1750_LightSensor_Mux::BH1750_LightSensor_Mux(
  MultiPlexer_TCA9548A* i2c,
  int address
) {
  _i2c = i2c;
  _address = address;
}

void BH1750_LightSensor_Mux::begin() {
}

float BH1750_LightSensor_Mux::read() {
  _lightMeter = new BH1750();

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
