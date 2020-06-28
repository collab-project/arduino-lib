/*
  NoisePalette.h
*/
#ifndef NoisePalette_h
#define NoisePalette_h

#include "Arduino.h"
#include <FastLED.h>

class NoisePalette {
  public:
    NoisePalette(CRGB* neopixels, uint16_t numLEDS);
    void loop();

  private:
    CRGB* _neopixels;
    uint16_t _numLEDS;
    uint16_t x;
    uint16_t y;
    uint16_t z;

    void ChangePaletteAndSettingsPeriodically();
    void fillnoise8();
    void mapNoiseToLEDsUsingPalette();
    void SetupRandomPalette();
    void SetupPurpleAndGreenPalette();
    void SetupBlackAndWhiteStripedPalette();
    uint16_t XY(uint8_t x, uint8_t y);
};

#endif