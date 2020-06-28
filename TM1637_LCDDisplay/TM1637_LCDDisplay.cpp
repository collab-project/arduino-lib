/*
  TM1637_LCDDisplay.cpp - Control 4 character 7-segment TM1637 LCD display.
*/

#include "TM1637_LCDDisplay.h"

/**
 * Constructor.
 *
 * @param clk_pin
 * @param dio_pin
 */
TM1637_LCDDisplay::TM1637_LCDDisplay(int clk_pin, int dio_pin) {
  _clkPin = clk_pin;
  _dioPin = dio_pin;

  // initialize communication interface and LCD
  m_lcd = new TM1637Display(_clkPin, _dioPin);
}

void TM1637_LCDDisplay::begin() {
  // no setup needed
}

void TM1637_LCDDisplay::clear() {
  m_lcd->clear();
}

void TM1637_LCDDisplay::setBrightness(uint8_t brightness, bool on) {
  m_lcd->setBrightness(brightness, on);
}
