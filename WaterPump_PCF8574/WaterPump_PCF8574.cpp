/*  Copyright (c) 2020-2021, Collab
 *  All rights reserved
*/

#include "WaterPump_PCF8574.h"

WaterPump_PCF8574::WaterPump_PCF8574(MultiPlexer_PCF8574* pcf, int relay_pin, bool normally_open) {
  _relayPin = relay_pin;
  _normallyOpen = normally_open;

  _relay = new SingleChannel_Relay_PCF8574(pcf, relay_pin, normally_open);
}

void WaterPump_PCF8574::begin() {
  _relay->begin();
}

void WaterPump_PCF8574::loop() {
}

void WaterPump_PCF8574::start() {
  _relay->start();
}

void WaterPump_PCF8574::stop() {
  _relay->stop();
}
