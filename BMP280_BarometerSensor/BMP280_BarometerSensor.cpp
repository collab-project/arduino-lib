/*  Copyright (c) 2020, Collab
 *  All rights reserved
*/
/*
  BMP280_BarometerSensor.cpp - Read BMP280 sensor.
*/
#include "BMP280_BarometerSensor.h"

#define SEALEVELPRESSURE_HPA ()

BMP280_BarometerSensor::BMP280_BarometerSensor(
  int scl_pin,
  int sda_pin,
  int address,
  int bus_nr,
  float sea_level_pressure,
  int clock_speed
) {
  _sclPin = scl_pin;
  _sdaPin = sda_pin;
  _address = address;
  _clockSpeed = clock_speed;
  _seaLevelPressure = sea_level_pressure;
  _i2c = new TwoWire(bus_nr);
  _sensor = new Adafruit_BMP280(_i2c);
}

void BMP280_BarometerSensor::begin() {
  _i2c->begin(_sdaPin, _sclPin, _clockSpeed);

  bool status;
  status = _sensor->begin(_address);
  if (!status) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
  }

  _sensor->setSampling(
    Adafruit_BMP280::MODE_NORMAL,
    Adafruit_BMP280::SAMPLING_X2,
    Adafruit_BMP280::SAMPLING_X16,
    Adafruit_BMP280::FILTER_X16,
    Adafruit_BMP280::STANDBY_MS_500
  );
}

void BMP280_BarometerSensor::loop() {
}

float BMP280_BarometerSensor::getTemperature() {
  return _sensor->readTemperature();
}

float BMP280_BarometerSensor::getPressure() {
  return _sensor->readPressure() / 100.0F;
}

float BMP280_BarometerSensor::getAltitude() {
  return _sensor->readAltitude(_seaLevelPressure);
}

BMP280_Result BMP280_BarometerSensor::readAll() {
  BMP280_Result result;

  result.array[0] = getTemperature();
  result.array[1] = getPressure();
  result.array[2] = getAltitude();

  return result;
}
