/*
  Fire.cpp
*/

#include <Fire.h>

/**
 * Random colored speckles that blink in and fade smoothly.
 */
Fire::Fire(CRGB* neopixels, uint16_t numLEDS) {
  _neopixels = neopixels;
  _numLEDS = numLEDS;
}

void Fire::loop() {
  // Array of temperature readings at each simulation cell
  uint8_t heat[_numLEDS];

  // Step 1. Cool down every cell a little
  for (int i = 0; i < _numLEDS; i++) {
    heat[i] = qsub8(heat[i], random8(0, ((COOLING * 10) / _numLEDS) + 2));
  }

  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for (int k= _numLEDS - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
  }

  // Step 3. Randomly ignite new 'sparks' of heat near the bottom
  if (random8() < SPARKING) {
    int y = random8(7);
    heat[y] = qadd8(heat[y], random8(160, 255) );
  }

  // Step 4. Map from heat cells to LED colors
  for (int j = 0; j < _numLEDS; j++) {
    CRGB color = HeatColor(heat[j]);
    int pixelnumber;
    if (gReverseDirection) {
      pixelnumber = (_numLEDS - 1) - j;
    } else {
      pixelnumber = j;
    }
    _neopixels[pixelnumber] = color;
  }
}
