/*  Copyright (c) 2020, Collab
 *  All rights reserved
*/
/*
  LED_MCP23017.h - Control LED light using MCP23017 multiplexer.
*/
#ifndef LED_MCP23017_h
#define LED_MCP23017_h

#include "Arduino.h"
#include <MultiPlexer_MCP23017.h>

class LED_MCP23017
{
  public:
    LED_MCP23017(
      int pin,
      MCP_PORT mcp_port,
      MultiPlexer_MCP23017* mcp,
      int led_state = LOW
    );
    int state;
    void begin();
    void loop();
    void enable();
    void disable();
    void toggle();

  private:
    void update();

    int _pin;
    MCP_PORT _port;
    MultiPlexer_MCP23017* _mcp;
};

#endif