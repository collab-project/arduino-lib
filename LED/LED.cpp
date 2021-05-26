/*  Copyright (c) 2020-2021, Collab
 *  All rights reserved
*/
/*
  LED.cpp - Control LED light.
*/

#include "LED.h"

LED::LED(int pin, int led_state) {
  _pin = pin;
  state = led_state;
}

void LED::begin() {
  pinMode(_pin, OUTPUT);
  update();
}

void LED::loop() {
  if (blinkEnabled) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= _blinkInterval) {
      previousMillis = currentMillis;
      if (state == LOW) {
        enable();
      } else {
        disable();
      }
    }
  }
}

void LED::update() {
  digitalWrite(_pin, state);
}

void LED::enable() {
  state = HIGH;
  update();
}

void LED::disable() {
  state = LOW;
  blinkEnabled = false;
  update();
}

void LED::blink(long blink_interval) {
  _blinkInterval = blink_interval;

  blinkEnabled = !blinkEnabled;
}
