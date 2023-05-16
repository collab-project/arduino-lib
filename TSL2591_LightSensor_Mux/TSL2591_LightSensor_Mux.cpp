/*  Copyright (c) 2023, Collab
 *  All rights reserved
*/
/*
  TSL2591_LightSensor.cpp - Read TSL2591 digital luminosity (light) sensor
  using a TCA9548A I2C expander.
*/
#include "TSL2591_LightSensor_Mux.h"

TSL2591_LightSensor_Mux::TSL2591_LightSensor_Mux(
    MultiPlexer_TCA9548A* expander,
    TwoWire* wire,
    uint8_t expander_channel,
    int address,
    int32_t sensor_id
) {
  _expander = expander;
  _i2c = wire;
  _expanderChannel = expander_channel;
  _address = address;
  _sensorID = sensor_id;

  _lightMeter = new Adafruit_TSL2591(_sensorID);
}

bool TSL2591_LightSensor_Mux::begin() {
  _expander->openChannel(_expanderChannel);

  working = _lightMeter->begin(_i2c, _address);

  _expander->closeChannel(_expanderChannel);

  return working;
}

float TSL2591_LightSensor_Mux::read() {
    _expander->openChannel(_expanderChannel);

    float lux;
    // get a new sensor event
    sensors_event_t event;
    _lightMeter->getEvent(&event);

    // calculate the result (light is measured in lux)
    if ((event.light == 0) |
        (event.light > 4294966000.0) |
        (event.light <-4294966000.0)) {
        /* If event.light = 0 lux the sensor is probably saturated
           and no reliable data could be generated!
           if event.light is +/- 4294967040 there was a float over/underflow */
        Log.warning(F("TSL2591: Invalid data (adjust gain or timing)" CR));

        lux = 0;
    } else {
        lux = event.light;
    }

    _expander->closeChannel(_expanderChannel);

    return lux;
}
