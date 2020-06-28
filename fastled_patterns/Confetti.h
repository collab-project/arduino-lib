/*
  Confetti.h
*/
#ifndef Confetti_h
#define Confetti_h

#include "Arduino.h"
#include <FastLED.h>

class Confetti {
  public:
    Confetti(CRGB* neopixels, uint16_t numLEDS);
    void loop(uint8_t gHue);

  private:
    CRGB* _neopixels;
    uint16_t _numLEDS;
};

#endif