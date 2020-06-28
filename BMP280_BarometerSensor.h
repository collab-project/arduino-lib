/*
  BMP280_BarometerSensor.h - Read BMP280 sensor.
*/
#ifndef BMP280_BarometerSensor_h
#define BMP280_BarometerSensor_h

#include "Arduino.h"
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

struct BMP280_Result {
    float array[3];
};

class BMP280_BarometerSensor
{
  public:
    BMP280_BarometerSensor() {};
    BMP280_BarometerSensor(
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
    BMP280_Result readAll();

  private:
    Adafruit_BMP280* _sensor;
    TwoWire* _i2c;
    int _sclPin;
    int _sdaPin;
    int _address;
    int _clockSpeed;
    float _seaLevelPressure;
};

#endif