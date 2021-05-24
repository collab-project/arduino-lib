/*
* Copyright (c) 2020-2021 Collab
* All rights reserved
*/
/*
  HD44780_LCDDisplay.h - Control 16x2 LCD display.
*/
#ifndef HD44780_LCDDisplay_h
#define HD44780_LCDDisplay_h

#include "Arduino.h"
#include <Wire.h>
#include <LiquidCrystal.h>

class HD44780_LCDDisplay {
  public:
    HD44780_LCDDisplay() {};
    HD44780_LCDDisplay(int rows, int columns, int rs, int en,
      int d4, int d5, int d6, int d7, int bl, int blLevel = HIGH);
    void begin();
    void clear();
    void home();
    void dim();
    void enable();
    void print(String msg);
    void setCursor(int col, int row);

    bool backlightActive = true;

  private:
    LiquidCrystal* _lcd;
    int _rows;
    int _columns;
};

#endif