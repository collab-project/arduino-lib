/*  Copyright (c) 2020, Collab
 *  All rights reserved
*/
/*
  SolenoidValve.cpp - Solenoid valve.
*/

#include "SolenoidValve.h"

/**
 * Constructor.
 *
 * @param relay_pin
 * @param normally_open
 */
SolenoidValve::SolenoidValve(int relay_pin, bool normally_open) {
  _relayPin = relay_pin;
  _normallyOpen = normally_open;

  _relay = new SingleChannel_Relay(_relayPin, normally_open);
}

void SolenoidValve::begin() {
  _relay->begin();
}

void SolenoidValve::loop() {
}

void SolenoidValve::start() {
  _relay->start();
}

void SolenoidValve::stop() {
  _relay->stop();
}
