/*  Copyright (c) 2020-2021, Collab
 *  All rights reserved
*/
/*
  BMP280_BarometerSensor.cpp - Read BMP280 sensor.
*/
#include "BMP280_BarometerSensor.h"

BMP280_BarometerSensor::BMP280_BarometerSensor(
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
  _busNr = bus_nr;
  _clockSpeed = clock_speed;
  _seaLevelPressure = sea_level_pressure;

  #if defined(__AVR__)
  _sensor = new Adafruit_BMP280();
  #elif defined(ESP8266) || defined(ESP32)
    // i2c
    if (_busNr == 1) {
      _i2c = new TwoWire(_busNr);
      _sensor = new Adafruit_BMP280(_i2c);
    } else {
      _sensor = new Adafruit_BMP280();
    }
  #endif
}

void BMP280_BarometerSensor::begin() {
  #if defined(ESP8266) || defined(ESP32)
  // i2c
  if (_busNr == 1) {
    _i2c->begin(_sdaPin, _sclPin, _clockSpeed);
  }
  #endif

  bool status;
  status = _sensor->begin(_address);
  if (!status) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
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

  result.temperature = getTemperature();
  result.pressure = getPressure();
  result.altitude = getAltitude();

  return result;
}
