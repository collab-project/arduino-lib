/*
  Confetti.cpp
*/

#include <Confetti.h>

/**
 * Random colored speckles that blink in and fade smoothly.
 */
Confetti::Confetti(CRGB* neopixels, uint16_t numLEDS) {
  _neopixels = neopixels;
  _numLEDS = numLEDS;
}

void Confetti::loop(uint8_t gHue) {
  fadeToBlackBy(_neopixels, _numLEDS, 10);
  int pos = random16(_numLEDS);
  _neopixels[pos] += CHSV(gHue + random8(64), 200, 255);
}
