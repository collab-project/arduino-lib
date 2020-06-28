/*
  BlendWave.h
*/
#ifndef BlendWave_h
#define BlendWave_h

#include "Arduino.h"
#include <FastLED.h>

// Use qsuba for smooth pixel colouring and qsubd for non-smooth pixel colouring
#define qsubd(x, b)  ((x>b)?b:0)                              // Digital unsigned subtraction macro. if result <0, then => 0. Otherwise, take on fixed value.
#define qsuba(x, b)  ((x>b)?x-b:0)                            // Analog Unsigned subtraction macro. if result <0, then => 0


class BlendWave {
  public:
    BlendWave(CRGB* neopixels, uint16_t numLEDS);
    void loop();

  private:
    CRGB* _neopixels;
    uint16_t _numLEDS;
    CRGBPalette16 currentPalette;                                 // Palette definitions
    CRGBPalette16 targetPalette;
    TBlendType currentBlending = LINEARBLEND;
};

#endif