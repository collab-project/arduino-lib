/*
  BeatsPerMinute.cpp
*/

#include <BeatsPerMinute.h>

/**
 * Colored stripes pulsing at a defined Beats-Per-Minute (BPM).
 */
BeatsPerMinute::BeatsPerMinute(CRGB* neopixels, uint16_t numLEDS, int bpm) {
  _neopixels = neopixels;
  _numLEDS = numLEDS;
  _beatsPerMinute = bpm;
}

void BeatsPerMinute::loop(uint8_t gHue) {
  CRGBPalette16 palette = CloudColors_p;
  uint8_t beat = beatsin8(_beatsPerMinute, 64, 255);
  for (int i = 0; i < _numLEDS; i++) {
    _neopixels[i] = ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10));
  }
}
