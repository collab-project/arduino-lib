/*
  HCSR04_DistanceSensor.h - Control HC-SR04 ultrasonic distance sensor.
*/
#ifndef HCSR04_DistanceSensor_h
#define HCSR04_DistanceSensor_h

#include "Arduino.h"
#include <HCSR04.h>

class HCSR04_DistanceSensor
{
  public:
    HCSR04_DistanceSensor() {};
    HCSR04_DistanceSensor(
      int trigger_pin,
      int echo_pin,
      int16_t temperature = 20,
      uint16_t max_distance = 300
    );
    float distance = 0;

    void begin();
    void loop();
    float measure(int16_t temperature);

  private:
    HCSR04* m_sensor;
    int _echoPin;
    int _triggerPin;
    float _temperature;
    float _maxDistance;
};

#endif