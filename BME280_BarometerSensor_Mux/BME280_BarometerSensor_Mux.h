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
#include <ArduinoLog.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <MultiPlexer_TCA9548A.h>

struct BME280_Result {
    float temperature;
    float pressure;
    float altitude;
    float humidity;
};

class BME280_BarometerSensor_Mux {
  public:
    BME280_BarometerSensor_Mux(
        MultiPlexer_TCA9548A* expander,
        uint8_t expander_channel = 0,
        int address = 0x76,
        float sea_level_pressure = 1013,
        int clock_speed = 100000
    );
    void begin();
    float getTemperature();
    float getPressure();
    float getAltitude();
    float getHumidity();
    BME280_Result readAll();

  private:
    uint8_t _expanderChannel;
    int _address;
    int _clockSpeed;
    float _seaLevelPressure;

    Adafruit_BME280* _sensor;
    MultiPlexer_TCA9548A* _expander;
};

#endif