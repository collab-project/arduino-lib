/*  Copyright (c) 2020, Collab
 *  All rights reserved
*/
/*
  Button_MCP23017.cpp - Control MCP23017 connected button.
*/
#ifndef Button_MCP23017_h
#define Button_MCP23017_h

#include <Arduino.h>
#include <Method.h>
#include <MultiPlexer_MCP23017.h>

class Button_MCP23017
{
  public:
    Button_MCP23017(
      int btn_pin,
      MCP_PORT mcp_port,
      MultiPlexer_MCP23017* mcp,
      Method callback
    );
    void loop();
    void begin();
    void read();

  private:
    int _btnPin;
    int _currentBtnState;
    int _lastBtnState;
    MCP_PORT _port;
    Method _callback;
    MultiPlexer_MCP23017* _mcp;
    unsigned long _lastDebounceTime = 0;
    unsigned long _debounceDelay = 5;
};

#endif
