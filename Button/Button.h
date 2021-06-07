/*  Copyright (c) 2020-2021, Collab
 *  All rights reserved
*/
/*
  Button.h - Control button.
*/
#ifndef Button_h
#define Button_h

#include <Arduino.h>
#include <Method.h>

class Button
{
  public:
    Button(int btn_pin, int pin_mode = INPUT);
    void loop();
    void begin(Method callback);
    void read();

  private:
    int _btnPin;
    int _pinMode;
    int _currentBtnState;
    int _lastBtnState;
    Method _callback;
    unsigned long _lastDebounceTime = 0;
    unsigned long _debounceDelay = 50;
};

#endif