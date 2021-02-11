/*  Copyright (c) 2021, Collab
 *  All rights reserved
*/
#ifndef WaterPump_h
#define WaterPump_h

#include <Arduino.h>
#include <SingleChannel_Relay.h>

class WaterPump
{
  public:
    WaterPump() {};
    WaterPump(int relay_pin, bool normally_open = false);
    void begin();
    void loop();
    void start();
    void stop();

  private:
    int _relayPin;
    bool _normallyOpen;
    SingleChannel_Relay* _relay;
};

#endif