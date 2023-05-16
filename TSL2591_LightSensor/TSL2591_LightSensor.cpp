/*  Copyright (c) 2023, Collab
 *  All rights reserved
*/
/*
  TSL2591_LightSensor.cpp - Read TSL2591 digital luminosity (light) sensor.
*/
#include "TSL2591_LightSensor.h"

TSL2591_LightSensor::TSL2591_LightSensor(
    TwoWire *theWire,
    uint8_t address,
    int32_t sensor_id
) {
    _i2c = theWire;
    _address = address;
    _sensorID = sensor_id;

    _lightMeter = new Adafruit_TSL2591(_sensorID);
}

bool TSL2591_LightSensor::begin() {
    working = _lightMeter->begin(_i2c, _address);
    return working;
}

void TSL2591_LightSensor::loop() {
}

float TSL2591_LightSensor::read() {
    float lux;

    // get a new sensor event
    sensors_event_t event;
    _lightMeter->getEvent(&event);

    // return the result (light is measured in lux)
    if ((event.light == 0) |
        (event.light > 4294966000.0) |
        (event.light <-4294966000.0)) {
        /* If event.light = 0 lux the sensor is probably saturated */
        /* and no reliable data could be generated! */
        /* if event.light is +/- 4294967040 there was a float over/underflow */
        Log.warning(F("TSL2591: Invalid data (adjust gain or timing)" CR));

        lux = 0;
    } else {
        lux = event.light;
    }

    return lux;
}

void TSL2591_LightSensor::displaySensorDetails() {
    sensor_t sensor;
    _lightMeter->getSensor(&sensor);

    Log.info(F("------------------------------------" CR));
    // sensor name
    Log.info(F("Sensor:       %s" CR), sensor.name);
    // version of the hardware + driver
    Log.info(F("Driver Ver:   %d" CR), sensor.version);
    // unique sensor identifier
    Log.info(F("Unique ID:    %d" CR), sensor.sensor_id);
    // maximum value of this sensor's value in SI units
    Log.info(F("Max Value:    %F lux" CR), sensor.max_value);
    // minimum value of this sensor's value in SI units
    Log.info(F("Min Value:    %F lux" CR), sensor.min_value);
    Log.info(F("------------------------------------" CR));
    Log.info(F("" CR));
}
