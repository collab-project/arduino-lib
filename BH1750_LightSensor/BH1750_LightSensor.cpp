/*
  BH1750_LightSensor.cpp - Read BH1750 light sensor.
*/
#include "BH1750_LightSensor.h"

BH1750_LightSensor::BH1750_LightSensor(int scl_pin, int sda_pin, int address, int bus_nr, int clock_speed) {
  _sclPin = scl_pin;
  _sdaPin = sda_pin;
  _address = address;
  _clockSpeed = clock_speed;
  _busNr = bus_nr;
}

void BH1750_LightSensor::begin() {
}

void BH1750_LightSensor::loop() {
}

float BH1750_LightSensor::read() {
  // init I2C bus for every read!
  _i2c = new TwoWire(_busNr);
  _lightMeter = new BH1750();
  _i2c->begin(_sdaPin, _sclPin, _clockSpeed);

  // make sure all is good
  if (_lightMeter->begin(BH1750::CONTINUOUS_HIGH_RES_MODE, _address, _i2c)) {
    // Serial.println(F("BH1750 ready."));
  } else {
    Serial.println(F("Error initialising BH1750"));
  }

  float lux = _lightMeter->readLightLevel();
  if (lux == -1) {
    // try one more time
    lux = _lightMeter->readLightLevel();
  }
  return lux;
}
