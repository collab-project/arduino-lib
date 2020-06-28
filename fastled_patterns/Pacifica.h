/*
  Pacifica.h
*/
#ifndef Pacifica_h
#define Pacifica_h

#include "Arduino.h"
#include <FastLED.h>

class Pacifica {
  public:
    Pacifica(CRGB* neopixels, uint16_t numLEDS);
    void loop();

  private:
    CRGB* _neopixels;
    uint16_t _numLEDS;
    CRGBPalette16 palette_1 = 
        { 0x000507, 0x000409, 0x00030B, 0x00030D, 0x000210, 0x000212, 0x000114, 0x000117, 
        0x000019, 0x00001C, 0x000026, 0x000031, 0x00003B, 0x000046, 0x14554B, 0x28AA50 };
    CRGBPalette16 palette_2 = 
        { 0x000507, 0x000409, 0x00030B, 0x00030D, 0x000210, 0x000212, 0x000114, 0x000117, 
        0x000019, 0x00001C, 0x000026, 0x000031, 0x00003B, 0x000046, 0x0C5F52, 0x19BE5F };
    CRGBPalette16 palette_3 = 
        { 0x000208, 0x00030E, 0x000514, 0x00061A, 0x000820, 0x000927, 0x000B2D, 0x000C33, 
        0x000E39, 0x001040, 0x001450, 0x001860, 0x001C70, 0x002080, 0x1040BF, 0x2060FF };

    void add_whitecaps();
    void deepen_colors();
    void one_layer(CRGBPalette16& p, uint16_t cistart, uint16_t wavescale, uint8_t bri, uint16_t ioff);
};

#endif