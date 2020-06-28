/*
  GL55xx_LightSensor.cpp - Read light dependent resistor (LDR).
*/
#include "GL55xx_LightSensor.h"

GL55xx_LightSensor::GL55xx_LightSensor(
    int pin,
    unsigned long resistor,
    LightDependentResistor::ePhotoCellKind kind,
    unsigned int adc_resolution
) {
  _ldr = new LightDependentResistor(pin, resistor, kind, adc_resolution);
  _ldr->setPhotocellPositionOnGround(false);
}

void GL55xx_LightSensor::begin() {
}

void GL55xx_LightSensor::loop() {
}

float GL55xx_LightSensor::read() {
  float intensity_in_lux = _ldr->getCurrentLux();

  return intensity_in_lux;
}
