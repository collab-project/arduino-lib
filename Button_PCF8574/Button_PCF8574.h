/*  Copyright (c) 2020, Collab
 *  All rights reserved
*/
/*
  Button_PCF8574.cpp - Control PCF8574 connected button.
*/
#ifndef Button_PCF8574_h
#define Button_PCF8574_h

#include <Arduino.h>
#include <Method.h>
#include <MultiPlexer_PCF8574.h>

class Button_PCF8574
{
  public:
    Button_PCF8574(
      int btn_pin,
      MultiPlexer_PCF8574* pcf,
      Method callback
    );
    void loop();
    void begin();
    void read();

  private:
    int _btnPin;
    int _currentBtnState;
    int _lastBtnState;
    Method _callback;
    MultiPlexer_PCF8574* _pcf;
    unsigned long _lastDebounceTime = 0;
    unsigned long _debounceDelay = 5;
};

#endif
