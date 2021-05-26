/*  Copyright (c) 2020-2021, Collab
 *  All rights reserved
*/
/*
  BMP280_BarometerSensor.h - Read BMP280 sensor.
*/
#ifndef BMP280_BarometerSensor_h
#define BMP280_BarometerSensor_h

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

struct BMP280_Result {
    float temperature;
    float pressure;
    float altitude;
};

class BMP280_BarometerSensor
{
  public:
    BMP280_BarometerSensor(
      int scl_pin,
      int sda_pin,
      int addresss = 0x76,
      int bus_nr = 1,
      float sea_level_pressure = 1013,
      long clock_speed = 100000
    );
    void begin();
    void loop();
    float getTemperature();
    float getPressure();
    float getAltitude();
    BMP280_Result readAll();

  private:
    Adafruit_BMP280* _sensor;
    TwoWire* _i2c;
    int _sclPin;
    int _sdaPin;
    int _address;
    int _busNr;
    int _clockSpeed;
    float _seaLevelPressure;
};

#endif