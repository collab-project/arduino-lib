/*  Copyright (c) 2020, Collab
 *  All rights reserved
*/
#ifndef WaterFloatSwitch_PCF8574_h
#define WaterFloatSwitch_PCF8574_h

#include <Arduino.h>
#include <Method.h>
#include <MultiPlexer_PCF8574.h>

class WaterFloatSwitch_PCF8574
{
  public:
    WaterFloatSwitch_PCF8574(
      int switch_pin,
      MultiPlexer_PCF8574* pcf,
      Method empty_callback
    );
    void begin();
    void loop();

  private:
    int _switchPin;
    MultiPlexer_PCF8574* _expander;

    // callbacks
    Method _emptyCallback;
};

#endif