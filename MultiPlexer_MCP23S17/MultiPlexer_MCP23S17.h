/*
* Copyright (c) 2021 Collab
* All rights reserved
*/
/*
  MultiPlexer_MCP23S17.h - Control MCP23S17 16-channel digital multiplexer over SPI.
*/
#ifndef MultiPlexer_MCP23S17_h
#define MultiPlexer_MCP23S17_h

#include <Arduino.h>
#include <SPI.h>
#include <Method.h>
#include <MCP23S17.h>
#include <ArduinoLog.h>

class MultiPlexer_MCP23S17
{
  public:
    MultiPlexer_MCP23S17(
      SPIClass *spi,
      int cs_pin,
      Method btn_callback,
      uint8_t addr = 0
    );
    void begin();
    void init();
    void loop();
    void interruptMCP(uint8_t port);
    void setupInterruptHandler(uint8_t irq_pin, void (*ISR)(void), int value);

    uint8_t address;
    const int totalPorts = 16;

  private:
    MCP23S17* _mcp;
    uint8_t _address;
    Method _btnCallback;

    /* 16-bit interrupt reading */
    volatile uint16_t _mcpReading = 0;
    /* 8-bit Port-A interrupt reading */
    volatile uint8_t _mcpAReading = 0;
    /* 8-bit Port-B interrupt reading */
    volatile uint8_t _mcpBReading = 0;

    /* number of bits set in byte */
    uint8_t _byteACount = 0;
    /* number of bits set in byte */
    uint8_t _byteBCount = 0;
    /* set bit array */
    uint8_t _byteABits[8] = {0};
    /* set bit array */
    uint8_t _byteBBits[8] = {0};

    volatile uint8_t _flagMCPA = 0;
    volatile uint8_t _flagINTA = 0;
    volatile uint8_t _flagMCPB = 0;
    volatile uint8_t _flagINTB = 0;

    void setPins();
    void processPins(uint8_t port);
    void print8Bits(uint8_t myByte);
    void readByteBits(uint8_t port);
    void readBankPortIntVal(uint8_t port);
    void readBankPortIntPins(uint8_t port);
};

#endif
