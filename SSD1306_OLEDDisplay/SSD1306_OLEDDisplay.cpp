/*  Copyright (c) 2020-2021, Collab
 *  All rights reserved
*/
/*
  SSD1306_OLEDDisplay.cpp - Control SSD1306 OLED display.
*/
#include "SSD1306_OLEDDisplay.h"

SSD1306_OLEDDisplay::SSD1306_OLEDDisplay(int sda_pin, int scl_pin, uint8_t address) {
  _sdaPin = sda_pin;
  _sclPin = scl_pin;
  _address = address;

  _display = new SSD1306Wire(address, sda_pin, scl_pin, GEOMETRY_128_32);
}

void SSD1306_OLEDDisplay::begin() {
  _display->init();
  _display->clear();
  _display->flipScreenVertically();
}

void SSD1306_OLEDDisplay::writeBig(String msg) {
  _display->init();
  _display->flipScreenVertically();
  _display->setTextAlignment(TEXT_ALIGN_CENTER);
  _display->setFont(Arimo_Regular_30);

  _display->drawString(64, 0, msg);

  _display->display();
}

void SSD1306_OLEDDisplay::writeSmall(String msg) {
  _display->init();
  _display->clear();
  _display->flipScreenVertically();
  _display->setTextAlignment(TEXT_ALIGN_CENTER);
  _display->setFont(Arimo_Regular_20);

  _display->drawString(64, 4, msg);

  _display->display();
}

void SSD1306_OLEDDisplay::disable() {
    _enabled = false;
    _display->init();
    _display->clear();
    _display->displayOff();
}

void SSD1306_OLEDDisplay::enable() {
  if (!_enabled) {
    _enabled = true;
    _display->displayOn();
  }
}
