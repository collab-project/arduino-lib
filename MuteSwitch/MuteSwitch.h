/*  Copyright (c) 2021, Collab
 *  All rights reserved
*/
#ifndef MuteSwitch_h
#define MuteSwitch_h

#include "Arduino.h"

class MuteSwitch
{
  public:
    MuteSwitch(int pin, int switch_state = LOW);
    int state;
    void begin();
    void loop();
    void enable();
    void disable();

  private:
    void update();
    int _pin;
};

#endif