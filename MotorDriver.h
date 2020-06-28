/*
  MotorDriver.h - Control H bridge module.
*/
#ifndef MotorDriver_h
#define MotorDriver_h

#include "Arduino.h"

class MotorDriver
{
  public:
    MotorDriver(int enable_pin, int pwma_pin, int pwmb_pin);
    void begin();
    void loop();
    void enable();
    void disable();

  private:
    int _enablePin;
    int _pwmaPin;
    int _pwmbPin;
};

#endif