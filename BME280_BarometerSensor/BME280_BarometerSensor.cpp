/*  Copyright (c) 2020, Collab
 *  All rights reserved
*/
/*
  BME280_BarometerSensor.cpp - Read BME280 sensor.
*/
#include "BME280_BarometerSensor.h"

BME280_BarometerSensor::BME280_BarometerSensor(
  int scl_pin,
  int sda_pin,
  int address,
  int bus_nr,
  float sea_level_pressure,
  long clock_speed
) {
  _sclPin = scl_pin;
  _sdaPin = sda_pin;
  _address = address;
  _clockSpeed = clock_speed;
  _seaLevelPressure = sea_level_pressure;
  _i2c = new TwoWire(bus_nr);
  _sensor = new Adafruit_BME280();
}

void BME280_BarometerSensor::begin() {
  _i2c->begin(_sdaPin, _sclPin, _clockSpeed);

  bool status;
  status = _sensor->begin(_address, _i2c);
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
  }
}

void BME280_BarometerSensor::loop() {
}

float BME280_BarometerSensor::getTemperature() {
  return _sensor->readTemperature();
}

float BME280_BarometerSensor::getPressure() {
  return _sensor->readPressure() / 100.0F;
}

float BME280_BarometerSensor::getAltitude() {
  return _sensor->readAltitude(_seaLevelPressure);
}

float BME280_BarometerSensor::getHumidity() {
  return _sensor->readHumidity();
}

BME280_Result BME280_BarometerSensor::readAll() {
  BME280_Result result;

  result.array[0] = getTemperature();
  result.array[1] = getPressure();
  result.array[2] = getHumidity();
  result.array[3] = getAltitude();

  return result;
}