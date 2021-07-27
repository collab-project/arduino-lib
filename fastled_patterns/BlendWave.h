/*
  BlendWave.h
*/
#ifndef BlendWave_h
#define BlendWave_h

#include "Arduino.h"
#include <FastLED.h>

// Use qsuba for smooth pixel colouring and qsubd for non-smooth pixel colouring
// Digital unsigned subtraction macro. if result <0, then => 0. Otherwise, take on fixed value.
#define qsubd(x, b)  ((x>b)?b:0)
// Analog Unsigned subtraction macro. if result <0, then => 0
#define qsuba(x, b)  ((x>b)?x-b:0)

class BlendWave {
  public:
    BlendWave(CRGB* neopixels, uint16_t numLEDS);
    void loop(CRGBPalette16 palette = OceanColors_p);

  private:
    CRGB* _neopixels;
    uint16_t _numLEDS;
    CRGBPalette16 _currentPalette;
    TBlendType _currentBlending = LINEARBLEND;
};

#endif