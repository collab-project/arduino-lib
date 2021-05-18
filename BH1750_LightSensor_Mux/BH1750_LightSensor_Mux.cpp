/*  Copyright (c) 2020-2021, Collab
 *  All rights reserved
*/
/*
  BH1750_LightSensor_Mux.cpp - Read BH1750 light sensor using a TCA9548A I2C expander.
*/
#include "BH1750_LightSensor_Mux.h"

BH1750_LightSensor_Mux::BH1750_LightSensor_Mux(
  MultiPlexer_TCA9548A* expander,
  uint8_t expander_channel,
  int address,
  BH1750::Mode modus
) {
  _expander = expander;
  _expanderChannel = expander_channel;
  _modus = modus;
  _address = address;

  _lightMeter = new BH1750(_address);
}

void BH1750_LightSensor_Mux::begin() {
  _expander->openChannel(_expanderChannel);

  bool status = _lightMeter->begin(_modus, _address, &Wire1);
  if (!status) {
    Serial.println(F("Error initialising BH1750 light sensor"));
  }

  _expander->closeChannel(_expanderChannel);
}

float BH1750_LightSensor_Mux::read() {
  _expander->openChannel(_expanderChannel);

  float lux = _lightMeter->readLightLevel();
  if (lux == -1) {
    // try one more time
    lux = _lightMeter->readLightLevel();
  }

  _expander->closeChannel(_expanderChannel);

  return lux;
}
