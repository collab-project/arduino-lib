/*
  HD44780_LCDDisplay.cpp - Control 16x2 LCD display.
*/

#include "HD44780_LCDDisplay.h"

/**
 * Constructor.
 */
HD44780_LCDDisplay::HD44780_LCDDisplay(
  int rows,
  int columns,
  int rs,
  int en,
  int d4,
  int d5,
  int d6,
  int d7,
  int bl,
  int blLevel
) {
  _rows = rows;
  _columns = columns;
 
   if (blLevel == 0) {
     backlightActive = false;
   }

  _lcd = new LiquidCrystal(rs, en, d4, d5, d6, d7, bl, POSITIVE);
}

/**
 * Initialize communication interface and LCD.
 */
void HD44780_LCDDisplay::begin() {
  // init LCD
  _lcd->begin(_columns, _rows);
}

/**
 * Print formatted data on the display.
 *
 * @param msg String data to print on display.
 */
void HD44780_LCDDisplay::print(String msg) {
  _lcd->print(msg);
}

/**
 * Clear the display and home the cursor.
 */
void HD44780_LCDDisplay::clear() {
  _lcd->clear();
}

/**
 * Home the cursor.
 */
void HD44780_LCDDisplay::home() {
  _lcd->home();
}

/**
 * Set cursor position.
 * 
 * @param col Column position.
 * @param row Row position.
 */
void HD44780_LCDDisplay::setCursor(int col, int row) {
  _lcd->setCursor(col, row);
}

/**
 * Disable screen and backlight.
 */
void HD44780_LCDDisplay::dim() {
  _lcd->off();

  backlightActive = false;
}

/**
 * Enable screen and backlight.
 */
void HD44780_LCDDisplay::enable() {
  _lcd->on();

  backlightActive = true;
}
