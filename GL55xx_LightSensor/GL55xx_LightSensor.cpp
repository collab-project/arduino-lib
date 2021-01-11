/*
  GL55xx_LightSensor.cpp - Read light dependent resistor (LDR).
*/
#include "GL55xx_LightSensor.h"

GL55xx_LightSensor::GL55xx_LightSensor(
    int pin,
    unsigned long resistor,
    LightDependentResistor::ePhotoCellKind kind,
    unsigned int adc_resolution,
    bool positionOnGround
) {
  _ldrPin = pin;
  _resistor = resistor;
  _kind = kind;
  _adcResolution = adc_resolution;
  _positionOnGround = positionOnGround;
}

void GL55xx_LightSensor::begin() {
  _ldr = new LightDependentResistor(_ldrPin, _resistor, _kind, _adcResolution);
  _ldr->setPhotocellPositionOnGround(_positionOnGround);
}

void GL55xx_LightSensor::loop() {
}

float GL55xx_LightSensor::read() {
  float intensity_in_lux = _ldr->getCurrentLux();

  return intensity_in_lux;
}
