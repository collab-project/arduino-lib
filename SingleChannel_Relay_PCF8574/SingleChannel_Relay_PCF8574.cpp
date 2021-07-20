/*  Copyright (c) 2020-2021, Collab
 *  All rights reserved
*/

#include "SingleChannel_Relay_PCF8574.h"

SingleChannel_Relay_PCF8574::SingleChannel_Relay_PCF8574(
  MultiPlexer_PCF8574* pcf, int relay_pin1, int relay_pin2, bool normally_open) {
  _expander = pcf;
  _relayPin1 = relay_pin1;
  _relayPin2 = relay_pin2;
  _normallyOpen = normally_open;
}

void SingleChannel_Relay_PCF8574::begin() {
}

void SingleChannel_Relay_PCF8574::loop() {
}

void SingleChannel_Relay_PCF8574::start() {
  int val;
  if (_normallyOpen == true) {
    // Normally Open configuration, send LOW signal to start current flow
    val = LOW;
  } else {
    val = HIGH;
  }
  write(val);
}

void SingleChannel_Relay_PCF8574::stop() {
  int val;
  if (_normallyOpen == true) {
    // Normally Open configuration, send HIGH signal stop current flow
    val = HIGH;
  } else {
    val = LOW;
  }
  write(val);
}

void SingleChannel_Relay_PCF8574::write(int val) {
  _expander->digitalWrite(_relayPin1, val);

  if (_relayPin2 != -1) {
    _expander->digitalWrite(_relayPin2, val);
  }
}
