/*  Copyright (c) 2020, Collab
 *  All rights reserved
*/
/*
   SingleChannel_Relay.h - Single channel relay.
*/
#ifndef SingleChannel_Relay_h
#define SingleChannel_Relay_h

#include "Arduino.h"

class SingleChannel_Relay
{
  public:
    SingleChannel_Relay() {};
    SingleChannel_Relay(int relay_pin, bool normally_open = true);
    void begin();
    void loop();
    void start();
    void stop();

  private:
    int _relayPin;
    bool _normallyOpen;
};

#endif