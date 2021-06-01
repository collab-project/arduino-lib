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

  lcd = new LiquidCrystal_I2C(address, _columns, _rows);
}

/**
 * Initialize communication interface and LCD.
 */
void HD44780_LCDDisplay_I2C::begin() {
  lcd->init();
  lcd->backlight();
}

/**
 * Print formatted data on the display.
 *
 * @param msg String data to print on display.
 */
void HD44780_LCDDisplay_I2C::print(String msg) {
  lcd->print(msg);
}

size_t HD44780_LCDDisplay_I2C::write(uint8_t value) {
  return lcd->write(value);
}

/**
 * Clear the display and home the cursor.
 */
void HD44780_LCDDisplay_I2C::clear() {
  lcd->clear();
}

/**
 * Home the cursor.
 */
void HD44780_LCDDisplay_I2C::home() {
  lcd->home();
}

/**
 * Set cursor position.
 *
 * @param col Column position.
 * @param row Row position.
 */
void HD44780_LCDDisplay_I2C::setCursor(int col, int row) {
  lcd->setCursor(col, row);
}

/**
 * Add custom character.
 *
 * @param location
 * @param charmap
 */
void HD44780_LCDDisplay_I2C::createChar(uint8_t location, uint8_t charmap[]) {
  lcd->createChar(location, charmap);
}

/**
 * Disable screen and backlight.
 */
void HD44780_LCDDisplay_I2C::dim() {
  lcd->noBacklight();

  backlightActive = false;
}

/**
 * Enable screen and backlight.
 */
void HD44780_LCDDisplay_I2C::enable() {
  lcd->backlight();

  backlightActive = true;
}

/**
 * Toggle screen and backlight.
 */
void HD44780_LCDDisplay_I2C::toggleBacklight() {
  backlightActive = !backlightActive;

  if (backlightActive) {
    enable();
  } else {
    dim();
  }
}
