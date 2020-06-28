/*
  Sinelon.h
*/
#ifndef Sinelon_h
#define Sinelon_h

#include "Arduino.h"
#include <FastLED.h>

class Sinelon {
  public:
    Sinelon(CRGB* neopixels, uint16_t numLEDS);
    void loop(uint8_t gHue);

  private:
    CRGB* _neopixels;
    uint16_t _numLEDS;
};

#endif