/*
* Copyright (c) 2021 Collab
* All rights reserved
*/
/*
  HD44780_LCDDisplay_I2C.cpp - Control 16x2 LCD I2C display.
*/

#include "HD44780_LCDDisplay_I2C.h"

/**
 * Constructor.
 */
HD44780_LCDDisplay_I2C::HD44780_LCDDisplay_I2C(
  int rows,
  int columns,
  uint8_t address,
  int blLevel
) {
  _rows = rows;
  _columns = columns;

   if (blLevel == 0) {
     backlightActive = false;
   }

  _lcd = new LiquidCrystal_I2C(address);
}

/**
 * Initialize communication interface and LCD.
 */
void HD44780_LCDDisplay_I2C::begin() {
  // init LCD
  _lcd->begin(_columns, _rows);
}

/**
 * Print formatted data on the display.
 *
 * @param msg String data to print on display.
 */
void HD44780_LCDDisplay_I2C::print(String msg) {
  _lcd->print(msg);
}

/**
 * Clear the display and home the cursor.
 */
void HD44780_LCDDisplay_I2C::clear() {
  _lcd->clear();
}

/**
 * Home the cursor.
 */
void HD44780_LCDDisplay_I2C::home() {
  _lcd->home();
}

/**
 * Set cursor position.
 *
 * @param col Column position.
 * @param row Row position.
 */
void HD44780_LCDDisplay_I2C::setCursor(int col, int row) {
  _lcd->setCursor(col, row);
}

/**
 * Disable screen and backlight.
 */
void HD44780_LCDDisplay_I2C::dim() {
  _lcd->off();

  backlightActive = false;
}

/**
 * Enable screen and backlight.
 */
void HD44780_LCDDisplay_I2C::enable() {
  _lcd->on();

  backlightActive = true;
}
