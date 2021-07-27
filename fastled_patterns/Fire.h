/*
  Fire.h
*/
#ifndef Fire_h
#define Fire_h

#include "Arduino.h"
#include <FastLED.h>

// COOLING: How much does the air cool as it rises?
// Less cooling = taller flames.  More cooling = shorter flames.
// Default 50, suggested range 20-100
#define COOLING  55

// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.
#define SPARKING 120

class Fire {
  public:
    Fire(CRGB* neopixels, uint16_t numLEDS);
    void loop();

  private:
    CRGB* _neopixels;
    uint16_t _numLEDS;

    bool gReverseDirection = false;
};

#endif