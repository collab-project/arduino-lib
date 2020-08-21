/*
  MultiPlexer_MCP23017.h - Control MCP23017 16-channel digital multiplexer.
*/
#ifndef MultiPlexer_MCP23017_h
#define MultiPlexer_MCP23017_h

#include <Arduino.h>
#include <MCP23017.h>

class MultiPlexer_MCP23017
{
  public:
    MultiPlexer_MCP23017(
      int reset_pin = -1,
      int i2c_addr = 0x20
    );
    void begin();
    void setPortMode(uint8_t val, MCP_PORT port);
    bool getPin(byte pin, MCP_PORT port);
    void setAllPins(MCP_PORT port, byte state);
    void setPin(byte pin, MCP_PORT port, byte state);
    void setPinX(uint8_t pin, MCP_PORT port, uint8_t ioDir, uint8_t state);
    void setPinMode(uint8_t pin, MCP_PORT port, uint8_t state);

  private:
    MCP23017* _mcp;
};

#endif