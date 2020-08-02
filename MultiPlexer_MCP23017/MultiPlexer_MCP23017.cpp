/*
  MultiPlexer_MCP23017.cpp - Control MCP23017 16-channel digital multiplexer.
*/

#include "MultiPlexer_MCP23017.h"

MultiPlexer_MCP23017::MultiPlexer_MCP23017(int reset_pin, int i2c_addr) {
  _mcp = new MCP23017(i2c_addr, reset_pin);
}

void MultiPlexer_MCP23017::begin() {
  _mcp->Init();
}

void MultiPlexer_MCP23017::setPortMode(uint8_t val, MCP_PORT port) {
  _mcp->setPortMode(val, port);
}

void MultiPlexer_MCP23017::setAllPins(MCP_PORT port, byte state) {
  _mcp->setAllPins(port, state);
}

void MultiPlexer_MCP23017::setPin(byte pin, MCP_PORT port, byte state) {
  _mcp->setPin(pin, port, state);
}

bool MultiPlexer_MCP23017::getPin(byte pin, MCP_PORT port) {
  return _mcp->getPin(pin, port);
}

void MultiPlexer_MCP23017::loop() {
}
