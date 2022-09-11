/*  Copyright (c) 2022, Collab
 *  All rights reserved
*/
#ifndef VibrationMotor_h
#define VibrationMotor_h

#include <Arduino.h>

class VibrationMotor
{
  public:
    VibrationMotor(
      int motor_pin,
      unsigned int period = 250
    );
    void begin();
    void loop();
    void enable();
    void disable();

  private:
    int _motorPin;
    unsigned int _period;
    unsigned int _enablePoint;

    bool _enabled = false;
};

#endif
