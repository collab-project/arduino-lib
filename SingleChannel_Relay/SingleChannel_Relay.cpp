/*  Copyright (c) 2020, Collab
 *  All rights reserved
*/
/*
  SingleChannel_Relay.cpp - Single channel relay.
*/

#include "SingleChannel_Relay.h"

/**
 * Constructor.
 *
 * @param relay_pin
 * @param normally_open
 */
SingleChannel_Relay::SingleChannel_Relay(int relay_pin, bool normally_open) {
  _relayPin = relay_pin;
  _normallyOpen = normally_open;
}

void SingleChannel_Relay::begin() {
  pinMode(_relayPin, OUTPUT);
}

void SingleChannel_Relay::loop() {
}

void SingleChannel_Relay::start() {
  if (_normallyOpen == true) {
    // Normally Open configuration, send LOW signal to start current flow
    digitalWrite(_relayPin, LOW);
  } else {
    digitalWrite(_relayPin, HIGH);
  }
}

void SingleChannel_Relay::stop() {
  if (_normallyOpen == true) {
    // Normally Open configuration, send HIGH signal stop current flow
    digitalWrite(_relayPin, HIGH);
  } else {
    digitalWrite(_relayPin, LOW);
  }
}
