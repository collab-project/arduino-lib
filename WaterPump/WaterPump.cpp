/*  Copyright (c) 2021, Collab
 *  All rights reserved
*/

#include "WaterPump.h"

WaterPump::WaterPump(int relay_pin, bool normally_open) {
  _relayPin = relay_pin;
  _normallyOpen = normally_open;

  _relay = new SingleChannel_Relay(relay_pin, normally_open);
}

void WaterPump::begin() {
  _relay->begin();
}

void WaterPump::loop() {
}

void WaterPump::start() {
  _relay->start();
}

void WaterPump::stop() {
  _relay->stop();
}
