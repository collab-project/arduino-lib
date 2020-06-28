/*
  BME280_BarometerSensor.h - Read BME280 sensor.
*/
#ifndef BME280_BarometerSensor_h
#define BME280_BarometerSensor_h

#include "Arduino.h"
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

struct BME280_Result {
    float array[4];
};

class BME280_BarometerSensor
{
  public:
    BME280_BarometerSensor() {};
    BME280_BarometerSensor(
      int scl_pin,
      int sda_pin,
      int addresss = 0x76,
      int bus_nr = 1,
      float sea_level_pressure = 1013,
      int clock_speed = 100000
    );
    void begin();
    void loop();
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