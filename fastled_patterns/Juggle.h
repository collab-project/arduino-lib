/*
  Juggle.h
*/
#ifndef Juggle_h
#define Juggle_h

#include "Arduino.h"
#include <FastLED.h>

class Juggle {
  public:
    Juggle(CRGB* neopixels, uint16_t numLEDS);
    void loop();

  private:
    CRGB* _neopixels;
    uint16_t _numLEDS;
};

#endif