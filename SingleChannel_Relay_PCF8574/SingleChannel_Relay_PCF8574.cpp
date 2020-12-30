/*  Copyright (c) 2020, Collab
 *  All rights reserved
*/

#include "SingleChannel_Relay_PCF8574.h"

SingleChannel_Relay_PCF8574::SingleChannel_Relay_PCF8574(
  MultiPlexer_PCF8574* pcf, int relay_pin, bool normally_open) {
  _expander = pcf;
  _relayPin = relay_pin;
  _normallyOpen = normally_open;
}

void SingleChannel_Relay_PCF8574::begin() {
  _expander->pinMode(_relayPin, OUTPUT, LOW);
}

void SingleChannel_Relay_PCF8574::loop() {
}

void SingleChannel_Relay_PCF8574::start() {
  if (_normallyOpen == true) {
    // Normally Open configuration, send LOW signal to start current flow
    _expander->digitalWrite(_relayPin, LOW);
  } else {
    _expander->digitalWrite(_relayPin, HIGH);
  }
}

void SingleChannel_Relay_PCF8574::stop() {
  if (_normallyOpen == true) {
    // Normally Open configuration, send HIGH signal stop current flow
    _expander->digitalWrite(_relayPin, HIGH);
  } else {
    _expander->digitalWrite(_relayPin, LOW);
  }
}
