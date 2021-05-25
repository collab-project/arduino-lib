/*
* Copyright (c) 2021 Collab
* All rights reserved
*/
/*
  HD44780_LCDDisplay_I2C.h - Control 16x2 LCD I2C display.
*/
#ifndef HD44780_LCDDisplay_I2C_h
#define HD44780_LCDDisplay_I2C_h

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class HD44780_LCDDisplay_I2C {
  public:
    HD44780_LCDDisplay_I2C(int rows, int columns, uint8_t address, int blLevel = HIGH);
    void begin();
    void clear();
    void home();
    void dim();
    void enable();
    void print(String msg);
    void setCursor(int col, int row);
    void createChar(uint8_t location, uint8_t charmap[]);
    size_t write(uint8_t value);

    bool backlightActive = true;
    LiquidCrystal_I2C* lcd;

  private:
    int _rows;
    int _columns;
};

#endif
