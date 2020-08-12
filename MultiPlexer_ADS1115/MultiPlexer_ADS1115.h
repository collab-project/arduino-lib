/*
  MultiPlexer_ADS1115.h - Control ADS1115 analog ADC.
*/
#ifndef MultiPlexer_ADS1115_h
#define MultiPlexer_ADS1115_h

#include <Arduino.h>
#include <Wire.h>
#include <ADS1115_WE.h>

struct ADS1115Result {
  int16_t channel0;
  int16_t channel1;
  int16_t channel2;
  int16_t channel3;
};

class MultiPlexer_ADS1115
{
  public:
    MultiPlexer_ADS1115(
      int16_t max_voltage,
      int16_t range_min = 0,
      int16_t range_max = 127,
      int i2c_addr = 0x48,
      ADS1115_RANGE voltage_range = ADS1115_RANGE_6144
    );
    void loop();
    void begin();
    ADS1115Result readAll();
    int16_t readChannel(ADS1115_MUX channel);
    int16_t readChannel0();
    int16_t readChannel1();
    int16_t readChannel2();
    int16_t readChannel3();

  private:
    int _i2cAddress;
    int16_t _maxVoltage;
    int16_t _rangeMin;
    int16_t _rangeMax;
    ADS1115_WE* _adc;
    ADS1115_RANGE _voltageRange;
};

#endif