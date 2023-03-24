/*  Copyright (c) 2020-2023, Collab
 *  All rights reserved
*/
/*
  LED_PCF8574.h - Control LED light using PCF8574 multiplexer.
*/

#include <LED_PCF8574.h>

LED_PCF8574::LED_PCF8574(
  int pin,
  MultiPlexer_PCF8574* pcf,
  int led_state
) {
  _pin = pin;
  _expander = pcf;
  state = led_state;
}

void LED_PCF8574::begin() {
  // set initial state
  update();
}

void LED_PCF8574::loop() {
  if (blink) {
    unsigned long currentMillis = millis();

    if (currentMillis - _previousMillis >= interval) {
      _previousMillis = currentMillis;

      toggle();
    }
  }
}

void LED_PCF8574::update() {
  _expander->digitalWrite(_pin, state);
}

void LED_PCF8574::enable() {
  state = HIGH;
  blink = false;
  update();
}

void LED_PCF8574::disable() {
  state = LOW;
  blink = false;
  update();
}

void LED_PCF8574::toggle() {
  state = !state;
  update();
}
