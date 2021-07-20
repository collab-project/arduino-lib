/*  Copyright (c) 2020-2021, Collab
 *  All rights reserved
*/

#ifndef SingleChannel_Relay_PCF8574_h
#define SingleChannel_Relay_PCF8574_h

#include "Arduino.h"
#include <MultiPlexer_PCF8574.h>

class SingleChannel_Relay_PCF8574
{
  public:
    SingleChannel_Relay_PCF8574() {};
    SingleChannel_Relay_PCF8574(
      MultiPlexer_PCF8574* pcf,
      int relay_pin,
      int relay_pin2 = -1,
      bool normally_open = true
    );
    void begin();
    void loop();
    void start();
    void stop();

  private:
    int _relayPin1;
    int _relayPin2;
    bool _normallyOpen;
    MultiPlexer_PCF8574* _expander;

    void write(int val);
};

#endif