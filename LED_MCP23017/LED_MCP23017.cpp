/*
  LED_MCP23017.h - Control LED light using MCP23017 multiplexer.
*/

#include "LED_MCP23017.h"

LED_MCP23017::LED_MCP23017(
  int pin,
  MCP_PORT mcp_port,
  MultiPlexer_MCP23017* mcp,
  int led_state
) {
  _pin = pin;
  _mcp = mcp;
  _port = mcp_port;
  state = led_state;
}

void LED_MCP23017::begin() {
}

void LED_MCP23017::loop() {
}

void LED_MCP23017::update() {
  _mcp->setPin(_pin, _port, state);
}

void LED_MCP23017::enable() {
  state = HIGH;
  update();
}

void LED_MCP23017::disable() {
  state = LOW;
  update();
}

void LED_MCP23017::toggle() {
  state = !state;
  update();
}
