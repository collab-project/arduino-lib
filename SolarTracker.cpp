/*
  SolarTracker.cpp - Track sun using 4 LDRs (light-dependent resistors).
*/

#include <SolarTracker.h>

SolarTracker::SolarTracker(
  int ldr_east_pin,
  int ldr_west_pin,
  int ldr_north_pin,
  int ldr_south_pin
) {
  _east = new GL55xx_LightSensor(ldr_east_pin);
  _west = new GL55xx_LightSensor(ldr_west_pin);
  _north = new GL55xx_LightSensor(ldr_north_pin);
  _south = new GL55xx_LightSensor(ldr_south_pin);
}

void SolarTracker::begin() {
  _east->begin();
  _west->begin();
  _north->begin();
  _south->begin();
}

Tracker_Result SolarTracker::read() {
  Tracker_Result result;

  result.array[0] = _east->read();
  result.array[1] = _west->read();
  result.array[2] = _north->read();
  result.array[3] = _south->read();

  return result;
}

void SolarTracker::loop() {
}
