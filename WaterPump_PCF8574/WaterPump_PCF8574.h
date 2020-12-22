/*  Copyright (c) 2020, Collab
 *  All rights reserved
*/
#ifndef WaterPump_PCF8574_h
#define WaterPump_PCF8574_h

#include <Arduino.h>
#include <MultiPlexer_PCF8574.h>
#include <SingleChannel_Relay_PCF8574.h>

class WaterPump_PCF8574
{
  public:
    WaterPump_PCF8574() {};
    WaterPump_PCF8574(MultiPlexer_PCF8574* pcf, int relay_pin, bool normally_open = false);
    void begin();
    void loop();
    void start();
    void stop();

  private:
    int _relayPin;
    bool _normallyOpen;
    SingleChannel_Relay_PCF8574* _relay;
};

#endif