/*
  Anemometer.cpp - Windspeed sensor.
*/

#include <Anemometer.h>

Anemometer::Anemometer(
    int pin,
    float voltage_min,
    float voltage_max,
    float wind_speed_min,
    float wind_speed_max,
    float wind_speed_protect
) {
  _pin = pin;
  _voltageMin = voltage_min;
  _voltageMax = voltage_max;
  _windSpeedMin = wind_speed_min;
  _windSpeedMax = wind_speed_max;
  _windSpeedProtect = wind_speed_protect;
}

void Anemometer::begin() {
}

void Anemometer::loop() {
}
