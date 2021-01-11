/*
  GL55xx_LightSensor.h - Read light dependent resistor (LDR).
*/
#ifndef GL55xx_LightSensor_h
#define GL55xx_LightSensor_h

#include "Arduino.h"
#include <LightDependentResistor.h>

class GL55xx_LightSensor
{
  public:
    GL55xx_LightSensor() {};
    GL55xx_LightSensor(
      int pin,
      unsigned long resistor = 10000,
      LightDependentResistor::ePhotoCellKind kind = LightDependentResistor::GL5516,
      unsigned int adc_resolution = 12,
      bool positionOnGround = false
    );
    void begin();
    void loop();
    float read();

  private:
    int _ldrPin;
    bool _positionOnGround;
    unsigned long _resistor;
    unsigned int _adcResolution;
    LightDependentResistor::ePhotoCellKind _kind;
    LightDependentResistor* _ldr;
};

#endif
