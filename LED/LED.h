/*  Copyright (c) 2020-2021, Collab
 *  All rights reserved
*/
/*
  LED.h - Control LED light.
*/
#ifndef LED_h
#define LED_h

#include "Arduino.h"

class LED
{
  public:
    LED() {};
    LED(int pin, int led_state = LOW);
    int state;
    void begin();
    void loop();
    void enable();
    void disable();
    void blink(long blink_interval = 450);

  private:
    void update();
    int _pin;
    long _blinkInterval;
    bool blinkEnabled = false;
    unsigned long previousMillis = 0;
};

#endif