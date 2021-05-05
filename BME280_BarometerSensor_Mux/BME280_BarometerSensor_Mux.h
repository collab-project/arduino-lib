/*  Copyright (c) 2020-2021, Collab
 *  All rights reserved
*/
/*
  BME280_BarometerSensor_Mux.h - Read BME280 sensor using a TCA9548A I2C expander.
*/
#ifndef BME280_BarometerSensor_Mux_h
#define BME280_BarometerSensor_Mux_h

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

struct BME280_Result {
    float array[4];
};

class BME280_BarometerSensor_Mux {
  public:
    BME280_BarometerSensor_Mux(
        int scl_pin,
        int sda_pin,
        int addresss = 0x76,
        int bus_nr = 1,
        float sea_level_pressure = 1013,
        int clock_speed = 100000);
    void begin();
    float getTemperature();
    float getPressure();
    float getAltitude();
    float getHumidity();
    BME280_Result readAll();

  private:
    Adafruit_BME280* _sensor;
    TwoWire* _i2c;
    int _sclPin;
    int _sdaPin;
    int _address;
    int _clockSpeed;
    float _seaLevelPressure;
};

#endif