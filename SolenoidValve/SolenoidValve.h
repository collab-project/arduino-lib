/*  Copyright (c) 2020, Collab
 *  All rights reserved
*/
#ifndef SolenoidValve_h
#define SolenoidValve_h

#include <Arduino.h>
#include <SingleChannel_Relay.h>

class SolenoidValve
{
  public:
    SolenoidValve() {};
    SolenoidValve(int relay_pin, bool normally_open = false);
    void begin();
    void loop();
    void start();
    void stop();

    bool active = false;

  private:
    SingleChannel_Relay* _relay;
    int _relayPin;
    bool _normallyOpen;
};

#endif