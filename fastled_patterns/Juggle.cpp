/*
  Juggle.cpp
*/

#include <Juggle.h>

/**
 * Eight colored dots, weaving in and out of sync with each other.
 */
Juggle::Juggle(CRGB* neopixels, uint16_t numLEDS) {
  _neopixels = neopixels;
  _numLEDS = numLEDS;
}

void Juggle::loop() {
  fadeToBlackBy(_neopixels, _numLEDS, 20);
  byte dothue = 0;
  for (int i = 0; i < 8; i++) {
    _neopixels[beatsin16(i + 7, 0, _numLEDS - 1)] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}
