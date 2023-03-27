/*  Copyright (c) 2020-2023, Collab
 *  All rights reserved
*/
/*
  BME280_BarometerSensor_Mux.cpp - Read BME280 sensor using a TCA9548A I2C expander.
*/
#include "BME280_BarometerSensor_Mux.h"

BME280_BarometerSensor_Mux::BME280_BarometerSensor_Mux(
    MultiPlexer_TCA9548A* expander,
    TwoWire* wire,
    uint8_t expander_channel,
    int address,
    float sea_level_pressure,
    int clock_speed
) {
  _expander = expander;
  _wire = wire;
  _expanderChannel = expander_channel;
  _address = address;
  _clockSpeed = clock_speed;
  _seaLevelPressure = sea_level_pressure;

  _sensor = new Adafruit_BME280();
}

bool BME280_BarometerSensor_Mux::begin() {
  _expander->openChannel(_expanderChannel);

  working = _sensor->begin(_address, _wire);

  _expander->closeChannel(_expanderChannel);

  return working;
}

float BME280_BarometerSensor_Mux::getTemperature() {
  return _sensor->readTemperature();
}

float BME280_BarometerSensor_Mux::getPressure() {
  return _sensor->readPressure() / 100.0F;
}

float BME280_BarometerSensor_Mux::getAltitude() {
  return _sensor->readAltitude(_seaLevelPressure);
}

float BME280_BarometerSensor_Mux::getHumidity() {
  return _sensor->readHumidity();
}

BME280_Result BME280_BarometerSensor_Mux::readAll() {
  _expander->openChannel(_expanderChannel);

  BME280_Result result;

  result.temperature = getTemperature();
  result.pressure = getPressure();
  result.humidity = getHumidity();
  result.altitude = getAltitude();

  _expander->closeChannel(_expanderChannel);

  return result;
}
