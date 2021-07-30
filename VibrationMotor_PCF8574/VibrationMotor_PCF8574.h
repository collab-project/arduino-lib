/*  Copyright (c) 2021, Collab
 *  All rights reserved
*/
#ifndef VibrationMotor_PCF8574_h
#define VibrationMotor_PCF8574_h

#include <Arduino.h>
#include <MultiPlexer_PCF8574.h>

class VibrationMotor_PCF8574
{
  public:
    VibrationMotor_PCF8574(
      int switch_pin,
      MultiPlexer_PCF8574* pcf,
      unsigned int period = 250
    );
    void begin();
    void loop();
    void enable();
    void disable();

  private:
    unsigned int _period;
    unsigned int _enablePoint;
    int _switchPin;
    bool _enabled = false;

    MultiPlexer_PCF8574* _expander;
};

#endif
