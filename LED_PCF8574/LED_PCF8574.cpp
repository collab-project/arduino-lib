/*
  LED_PCF8574.h - Control LED light using PCF8574 multiplexer.
*/

#include "LED_PCF8574.h"

LED_PCF8574::LED_PCF8574(
  int pin,
  MultiPlexer_PCF8574* pcf,
  int led_state
) {
  _pin = pin;
  _pcf = pcf;
  state = led_state;
}

void LED_PCF8574::begin() {
	_pcf->pinMode(_pin, OUTPUT);
}

void LED_PCF8574::loop() {
}

void LED_PCF8574::update() {
  _pcf->digitalWrite(_pin, state);
}

void LED_PCF8574::enable() {
  state = HIGH;
  update();
}

void LED_PCF8574::disable() {
  state = LOW;
  update();
}

void LED_PCF8574::toggle() {
  state = !state;
  update();
}
