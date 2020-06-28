/*
  Anemometer.h - Windspeed sensor.
*/
#ifndef Anemometer_h
#define Anemometer_h

#include <Arduino.h>
#include <Method.h>

class Anemometer
{
  public:
    Anemometer() {};
    Anemometer(
      int pin,
      float voltage_min,
      float voltage_max,
      float wind_speed_min,
      float wind_speed_max,
      float wind_speed_protect
    );
    void loop();
    void begin();

  private:
    int _pin;
    float _voltageMin;
    float _voltageMax;
    float _windSpeedMin;
    float _windSpeedMax;
    float _windSpeedProtect;
};

#endif