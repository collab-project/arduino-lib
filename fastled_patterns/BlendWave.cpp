/*
  BlendWave.cpp
*/

#include <BlendWave.h>

/**
 * Constructor.
 */
BlendWave::BlendWave(CRGB* neopixels, uint16_t numLEDS) {
  _neopixels = neopixels;
  _numLEDS = numLEDS;
}

void BlendWave::loop(CRGBPalette16 palette) {
  _currentPalette = palette;

  // setting phase change for a couple of waves
  int thisPhase = beatsin8(6, -64, 64);
  int thatPhase = beatsin8(7, -64, 64);

  // for each of the LED's in the strand, set a brightness based on a wave as follows:
  for (int k=0; k<_numLEDS; k++) {

    // create a wave and add a phase change and add another wave with its own phase change
    int colorIndex = cubicwave8((k*23)+thisPhase)/2 + cos8((k*15)+thatPhase)/2;
    // qsub gives it a bit of 'black' dead space by setting sets a minimum value.
    // If colorIndex < current value of beatsin8(), then bright = 0. Otherwise, bright = colorIndex..
    int thisBright = qsuba(colorIndex, beatsin8(7,0,96));

    // Add the foreground colour
    _neopixels[k] = ColorFromPalette(_currentPalette, colorIndex, thisBright, _currentBlending);
  }
}
