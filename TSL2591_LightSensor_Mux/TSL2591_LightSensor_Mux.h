/*  Copyright (c) 2023, Collab
 *  All rights reserved
*/
/*
  TSL2591_LightSensor_Mux.h - Read TSL2591 digital luminosity (light) sensor
  using a TCA9548A I2C expander.
*/
#ifndef TSL2591_LightSensor_Mux_h
#define TSL2591_LightSensor_Mux_h

#include <Arduino.h>
#include <Wire.h>
#include <ArduinoLog.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2591.h>
#include <MultiPlexer_TCA9548A.h>

class TSL2591_LightSensor_Mux
{
  public:
    TSL2591_LightSensor_Mux(
      MultiPlexer_TCA9548A* expander,
      TwoWire* wire,
      uint8_t expander_channel,
      int address = TSL2591_ADDR,
      int32_t sensor_id = 2591
    );
    bool begin();
    float read();

    bool working = true;

  private:
    int _address;
    int32_t _sensorID;
    uint8_t _expanderChannel;

    TwoWire* _i2c;
    Adafruit_TSL2591* _lightMeter;
    MultiPlexer_TCA9548A* _expander;
};

#endif
