/*  Copyright (c) 2020-2023, Collab
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
    Button(int btn_pin, int pin_mode = INPUT, int last_state = LOW, int active_state = HIGH);
    void loop();
    void begin(Method callback);
    void read();

  private:
    int _btnPin;
    int _pinMode;
    int _currentBtnState;
    int _lastBtnState;
    int _activeState;
    Method _callback;
    unsigned long _lastDebounceTime = 0;
    unsigned long _debounceDelay = 50;
};

#endif