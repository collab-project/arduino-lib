/*
  Potentiometer_ADS1115.cpp - Control potentiometer using ADS1115.
*/
#ifndef Potentiometer_ADS1115_h
#define Potentiometer_ADS1115_h

#include <Arduino.h>
#include <Method.h>
#include <MultiPlexer_ADS1115.h>

class Potentiometer_ADS1115
{
  public:
    Potentiometer_ADS1115(
      int channel,
      MultiPlexer_ADS1115* adc,
      Method callback
    );
    void loop();
    void begin();
    void read();

  private:
    int _channel;
    float _val;
    float _prev;
    Method _callback;
    MultiPlexer_ADS1115* _adc;
};

#endif
