/*
  BeatsPerMinute.h
*/
#ifndef BeatsPerMinute_h
#define BeatsPerMinute_h

#include "Arduino.h"
#include <FastLED.h>

class BeatsPerMinute {
  public:
    BeatsPerMinute();
    BeatsPerMinute(CRGB* neopixels, uint16_t numLEDS, int bpm = 87);
    void loop(uint8_t gHue);

  private:
    CRGB* _neopixels;
    uint16_t _numLEDS;
    uint8_t _beatsPerMinute;
};

#endif