/*
* Copyright (c) 2021 Collab
* All rights reserved
*/
/*
  MultiPlexer_MCP23S17.cpp - Control MCP23S17 16-channel digital multiplexer over SPI.
*/

#include "MultiPlexer_MCP23S17.h"

MultiPlexer_MCP23S17::MultiPlexer_MCP23S17(SPIClass *spi, int cs_pin, Method btn_callback, uint8_t addr) {
  address = addr;
  _btnCallback = btn_callback;

  _mcp = new MCP23S17(spi, cs_pin, addr);
}

void MultiPlexer_MCP23S17::begin() {
  _mcp->begin();
}

void MultiPlexer_MCP23S17::init() {
  // set MCP23S17 pin modes and interrupt configurations
  // to set one pin: chip.pinMode(0, INPUT_PULLUP);
  setPins();

  // clear the interrupt value variables
  _mcpAReading = 0;
  _mcpBReading = 0;
  _mcpReading = 0;
}

void MultiPlexer_MCP23S17::setupInterruptHandler(uint8_t irq_pin, void (*ISR)(void), int value) {
  pinMode(irq_pin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(irq_pin), ISR, value);
}

/**
 * Runs the MCP Interrupt processing from the Arduino ISR
 * and then takes action (prints) on the MCP pins that went LOW.
*/
void MultiPlexer_MCP23S17::loop() {
  if (_flagMCPA > 0) {
    //Log.info(F("loop flagMCPA" CR));

    // get the bit count and write the bits to byteBit[] array
    readByteBits(0);

    // do some processing of each interrupted pin
    processPins(0);

    _flagMCPA = 0;
  }

  if (_flagMCPB > 0) {
    //Log.info(F("loop flagMCPB" CR));

    readByteBits(1);

    // do some processing of each interrupted pin
    processPins(1);

    _flagMCPB = 0;
  }
}

/**
 * Set all port expander pins to desired mode INPUT_PULLUP.
 * Set all port expander input pins interrupts
*/
void MultiPlexer_MCP23S17::setPins() {
  for (uint8_t ind = 0; ind <= totalPorts - 1; ind++) {
    _mcp->pinMode(ind, INPUT_PULLUP);
    _mcp->enableInterrupt(ind, FALLING);
  }

  // set port expander interrupt configuratons
  _mcp->setMirror(false);
  _mcp->setInterruptOD(false);
  _mcp->setInterruptLevel(LOW);

  // clear all interrupts on this port expander
  _mcpReading = _mcp->getInterruptValue();
}

/**
 * Take action on new pin interrupt values
*/
void MultiPlexer_MCP23S17::interruptMCP(uint8_t port) {
  // read the Port Expander Interrupt pins
  readBankPortIntPins(port);

  // read the Port Expander Interrupt values
  readBankPortIntVal(port);

  // take action on new pin interrupt values
  if (port < 1) {
    // set flag that Port A interrupt occurred
    _flagMCPA = 1;
  } else {
    // set flag that Port B interrupt occurred
    _flagMCPB = 1;
  }
}

/**
 * Process the port byteBits array of interrupted MCP pins
*/
void MultiPlexer_MCP23S17::processPins(uint8_t port) {
  uint8_t pin;
  if (port < 1) {
    // Port A
    // _byteACount = number of pins to process
    for (uint8_t ind = 0; ind < _byteACount; ind++) {
      // recover the bit number from sequential array
      pin = _byteABits[ind];

      // notify listeners
      _btnCallback.callback3IntArg(address, port, pin);
    }
  } else {
    // Port B
    // _byteBCount = number of pins to process
    for (uint8_t ind = 0; ind < _byteBCount; ind++) {
      // recover the bit number from sequential array
      pin = _byteBBits[ind];

      // notify listeners
      _btnCallback.callback3IntArg(address, port, pin);
    }
  }
}

/**
 * Read all Port Expander port interrupt pins.
 * save set bit to byteBits arrays
 * byteBits array can be sequentially processed later
*/
void MultiPlexer_MCP23S17::readByteBits(uint8_t port) {
  if (port < 1) {
    // Port A
    _byteACount = 0;
    for (uint8_t ind = 0; ind < 8; ind++) {
      // ~ inverts bit values
      if (bitRead(~_mcpAReading, ind)) {
        // save the bit number to sequential array
        _byteABits[_byteACount] = ind;
        _byteACount = _byteACount + 1;
        //Log.info(F("Port A whichBit: %d" CR), ind);
      }
    }
    //Log.info(F("_byteACount: %d" CR), _byteACount);
  } else {
    // Port B
    _byteBCount = 0;
    for (uint8_t ind = 0; ind < 8; ind++) {
      // ~ inverts bit values
      if (bitRead(~_mcpBReading, ind)) {
        // save the bit number to sequential array
        _byteBBits[_byteBCount] = ind;
        _byteBCount = _byteBCount + 1;
        //Log.info(F("Port B whichBit: %d" CR), ind);
      }
    }
    //Log.info(F("_byteBCount: %d" CR, _byteBCount);
  }
}

/**
 * Read all Port Expander port interrupt values
*/
void MultiPlexer_MCP23S17::readBankPortIntVal(uint8_t port) {
  if (port < 1) {
    // Port A
    _mcpAReading = _mcp->getInterruptAValue();
    //Log.info(F("Port A Interrupt Values: ")); print8Bits(_mcpAReading);
  } else {
    // Port B
    _mcpBReading = _mcp->getInterruptBValue();
    //Log.info(F("Port B Interrupt Values: ")); print8Bits(_mcpBReading);
  }
}

/**
 * Read all Port Expander port interrupt pins
*/
void MultiPlexer_MCP23S17::readBankPortIntPins(uint8_t port) {
  if (port < 1) {
    // Port A
    _mcpAReading = _mcp->getInterruptAPins();
  } else {
    // Port B
    _mcpBReading = _mcp->getInterruptBPins();
  }
}

void MultiPlexer_MCP23S17::print8Bits(uint8_t myByte) {
  for (uint8_t mask = 0x80; mask; mask >>= 1) {
    if (mask & myByte)
      Log.info(F("1"));
    else
      Log.info(F("0"));
  }
}
