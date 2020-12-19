/*  Copyright (c) 2020, Collab
 *  All rights reserved
*/
/*
  RCWL0516_MovementSensor.h - Control RCWL-0516 movement sensor.
*/
#ifndef RCWL0516_MovementSensor_h
#define RCWL0516_MovementSensor_h

#include <Arduino.h>
#include <Method.h>

class RCWL0516_MovementSensor {
  public:
    RCWL0516_MovementSensor() {};
    RCWL0516_MovementSensor(int sensor_pin, Method movementStart_callback, Method movementStop_callback);
    void begin();
    void loop();
    bool enabled = true;

  private:
    int _sensorPin;
    int _value = -1;
    int _prevReading = -1;
    Method _movementStartCallback;
    Method _movementStopCallback;
};

#endif