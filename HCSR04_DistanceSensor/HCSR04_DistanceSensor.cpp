/*
  HCSR04_DistanceSensor.cpp - Control HC-SR04 ultrasonic distance sensor.
*/

#include "HCSR04_DistanceSensor.h"

/**
 * Constructor.
 *
 * @param trigger_pin
 * @param echo_pin
 * @param temperature Ambient temperature, in degrees Celsius
 * @param max_distance Maximum measuring distance, in centimeters
 */
HCSR04_DistanceSensor::HCSR04_DistanceSensor(
  int trigger_pin,
  int echo_pin,
  int16_t temperature,
  uint16_t max_distance
) {
  _triggerPin = trigger_pin;
  _echoPin = echo_pin;
  _temperature = temperature;
  _maxDistance = max_distance;

  m_sensor = new HCSR04(_triggerPin, _echoPin, _temperature, _maxDistance);
}

void HCSR04_DistanceSensor::begin() {
  //set trigger as output & echo pins as input
  m_sensor->begin();
}

void HCSR04_DistanceSensor::loop() {
}

float HCSR04_DistanceSensor::measure(int16_t temperature) {
  _temperature = temperature;

  // update temperature
  m_sensor->setTemperature(_temperature);

  distance = m_sensor->getMedianFilterDistance();

  if (distance == HCSR04_OUT_OF_RANGE) {
    distance = -1;
  }

  return distance;
}
