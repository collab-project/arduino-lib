/*  Copyright (c) 2020-2021, Collab
 *  All rights reserved
*/
/*
  BME280_BarometerSensor_Mux.cpp - Read BME280 sensor using a TCA9548A I2C expander.
*/
#include "BME280_BarometerSensor_Mux.h"

BME280_BarometerSensor_Mux::BME280_BarometerSensor_Mux(
    MultiPlexer_TCA9548A* expander,
    uint8_t expander_channel,
    int address,
    float sea_level_pressure,
    int clock_speed
) {
  _expander = expander;
  _expanderChannel = expander_channel;
  _address = address;
  _clockSpeed = clock_speed;
  _seaLevelPressure = sea_level_pressure;

  _sensor = new Adafruit_BME280();
}

void BME280_BarometerSensor_Mux::begin() {
  _expander->openChannel(_expanderChannel);

  bool status = _sensor->begin(_address, &Wire1);
  if (!status) {
    Serial.println(F("Error initialising BME280 sensor"));
  }

  _expander->closeChannel(_expanderChannel);
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
