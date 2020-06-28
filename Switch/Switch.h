/*
  Switch.h - Control switch button.
*/
#ifndef Switch_h
#define Switch_h

#include "Arduino.h"

class Switch
{
  public:
    Switch() {};
    Switch(int switch_pin);
    void begin();

  private:
    int _switchPin;
};

#endif