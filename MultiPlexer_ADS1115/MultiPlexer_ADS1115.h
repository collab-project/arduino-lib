/*
  MultiPlexer_ADS1115.h - Control ADS1115 analog ADC.
*/
#ifndef MultiPlexer_ADS1115_h
#define MultiPlexer_ADS1115_h

#include <Arduino.h>
#include <Wire.h>
#include <ADS1115_WE.h>

struct ADS1115Result {
  float channel0;
  float channel1;
  float channel2;
  float channel3;
};

class MultiPlexer_ADS1115
{
  public:
    MultiPlexer_ADS1115(
      float max_voltage,
      int i2c_addr = 0x48,
      ADS1115_RANGE voltage_range = ADS1115_RANGE_6144
    );
    void loop();
    void begin();
    ADS1115Result readAll();
    float readChannel(ADS1115_MUX channel);
    float readChannel0();
    float readChannel1();
    float readChannel2();
    float readChannel3();

  private:
    int _i2cAddress;
    int _maxVoltage;
    ADS1115_WE* _adc;
    ADS1115_RANGE _voltageRange;
};

#endif