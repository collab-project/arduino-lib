/*
  TM1637_LCDDisplay.h - Control 4 character 7-segment TM1637 LCD display.
*/
#ifndef TM1637_LCDDisplay_h
#define TM1637_LCDDisplay_h

#include "Arduino.h"
#include <TM1637Display.h>

class TM1637_LCDDisplay
{
  public:
    TM1637_LCDDisplay() {};
    TM1637_LCDDisplay(int clk_pin, int dio_pin);
    void begin();
    void clear();
    void setBrightness(uint8_t brightness, bool on);

  private:
    TM1637Display* m_lcd;
    int _clkPin;
    int _dioPin;
};

#endif