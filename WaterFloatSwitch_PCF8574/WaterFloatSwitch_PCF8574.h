/*  Copyright (c) 2020-2021, Collab
 *  All rights reserved
*/
#ifndef WaterFloatSwitch_PCF8574_h
#define WaterFloatSwitch_PCF8574_h

#include <Arduino.h>
#include <MultiPlexer_PCF8574.h>

class WaterFloatSwitch_PCF8574
{
  public:
    WaterFloatSwitch_PCF8574(
      int switch_pin,
      MultiPlexer_PCF8574* pcf
    );
    void begin();
    uint8_t read();
    bool isEmpty();

  private:
    int _switchPin;
    bool _empty = false;
    int _lastState = LOW;

    MultiPlexer_PCF8574* _expander;
};

#endif