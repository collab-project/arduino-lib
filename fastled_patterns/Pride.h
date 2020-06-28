/*
  Pride.h
*/
#ifndef Pride_h
#define Pride_h

#include "Arduino.h"
#include <FastLED.h>

class Pride {
  public:
    Pride(CRGB* neopixels, uint16_t numLEDS);
    void loop();

  private:
    CRGB* _neopixels;
    uint16_t _numLEDS;
};

#endif