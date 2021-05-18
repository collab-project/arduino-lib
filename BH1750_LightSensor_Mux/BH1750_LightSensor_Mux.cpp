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
  BH1750Mode modus
) {
  _expander = expander;
  _expanderChannel = expander_channel;
  _modus = modus;
  _address = address;

  _lightMeter = new BH1750_WE(&Wire1, _address);
}

void BH1750_LightSensor_Mux::begin() {
  _expander->openChannel(_expanderChannel);

  _lightMeter->init();
  _lightMeter->setMode(_modus);

  _expander->closeChannel(_expanderChannel);
}

float BH1750_LightSensor_Mux::read() {
  _expander->openChannel(_expanderChannel);

  float lux = _lightMeter->getLux();

  _expander->closeChannel(_expanderChannel);

  return lux;
}
