/*
  Sinelon.cpp
*/

#include <Sinelon.h>

/**
 * A colored dot sweeping back and forth, with fading trails.
 */
Sinelon::Sinelon(CRGB* neopixels, uint16_t numLEDS) {
  _neopixels = neopixels;
  _numLEDS = numLEDS;
}

void Sinelon::loop(uint8_t gHue) {
  fadeToBlackBy(_neopixels, _numLEDS, 5);
  int pos = beatsin16(13, 0, _numLEDS - 1);
  _neopixels[pos] += CHSV(gHue, 255, 192);
}
