/*  Copyright (c) 2023, Collab
 *  All rights reserved
*/
/*
  TSL2591_LightSensor.h - Read TSL2591 digital luminosity (light) sensor.
*/
#ifndef TSL2591_LightSensor_h
#define TSL2591_LightSensor_h

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2591.h>
#include <ArduinoLog.h>

class TSL2591_LightSensor
{
  public:
    TSL2591_LightSensor(
      TwoWire *theWire,
      uint8_t address = TSL2591_ADDR,
      int32_t sensor_id = 2591
    );
    bool begin();
    void loop();
    float read();
    void displaySensorDetails();

    bool working = true;

  private:
    Adafruit_TSL2591* _lightMeter;
    TwoWire* _i2c;

    uint8_t _address;
    int32_t _sensorID;
};

#endif