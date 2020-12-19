/*
  LED_PCF8574.h - Control LED light using PCF8574 multiplexer.
*/
#ifndef LED_PCF8574_h
#define LED_PCF8574_h

#include "Arduino.h"
#include <MultiPlexer_PCF8574.h>

class LED_PCF8574
{
  public:
    LED_PCF8574(
      int pin,
      MultiPlexer_PCF8574* pcf,
      int led_state = LOW
    );
    int state;
    void begin();
    void loop();
    void enable();
    void disable();
    void toggle();

  private:
    void update();

    int _pin;
    MultiPlexer_PCF8574* _pcf;
};

#endif