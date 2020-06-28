/*
  FC28_SoilSensor.cpp - Read FC-28 soil moisture sensor.
*/
#include "FC28_SoilSensor.h"

FC28_SoilSensor::FC28_SoilSensor(int soil_pin) {
  _soilPin = soil_pin;
}

void FC28_SoilSensor::begin() {
}

void FC28_SoilSensor::loop() {
}

int FC28_SoilSensor::measure() {
  return analogRead(_soilPin);
}

int FC28_SoilSensor::measurePercentage() {
  // read the input
  int output_value = measure();

  // map to percentage
  return map(output_value, 0, 4095, 100, 0);
}
