/*
  Potentiometer_ADS1115.cpp - Control potentiometer using ADS1115.
*/
#ifndef Potentiometer_ADS1115_h
#define Potentiometer_ADS1115_h

#include <Arduino.h>
#include <Method.h>
#include <Deadband.h>
#include <MultiPlexer_ADS1115.h>

class Potentiometer_ADS1115
{
  public:
    Potentiometer_ADS1115(
      int channel,
      int16_t max_voltage,
      int16_t range_min,
      int16_t range_max,
      MultiPlexer_ADS1115* adc,
      Method callback
    );
    void loop();
    void begin();
    void read();

  private:
    int _channel;
    int16_t _val;
    int16_t _prev;
    int16_t _rangeMin;
    int16_t _rangeMax;
    int16_t _maxVoltage;
    const int _widthOfDeadbandInBits = 1;

    Method _callback;
    DeadbandFilter* _filter;
    MultiPlexer_ADS1115* _adc;
};

#endif
