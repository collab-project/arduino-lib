/*  Copyright (c) 2021, Collab
 *  All rights reserved
*/
/*
  SSD1306_OLEDDisplay_Mux.cpp - Control SSD1306 OLED display using TCA9548A expander.
*/

#include <MultiPlexer_TCA9548A.h>
#include <SSD1306_OLEDDisplay_Mux.h>

SSD1306_OLEDDisplay_Mux::SSD1306_OLEDDisplay_Mux(
  MultiPlexer_TCA9548A* expander,
  uint8_t address,
  OLEDDISPLAY_GEOMETRY size
) {
  _expander = expander;
  _address = address;

  _display = new SSD1306Wire(
    address,
    _expander->sdaPin,
    _expander->sclPin,
    size
  );
}

void SSD1306_OLEDDisplay_Mux::begin() {
  _display->init();
  _display->clear();
  _display->flipScreenVertically();
}

void SSD1306_OLEDDisplay_Mux::writeBig(String msg) {
  _display->init();
  _display->flipScreenVertically();
  _display->setTextAlignment(TEXT_ALIGN_CENTER);
  _display->setFont(Arimo_Regular_30);

  _display->drawString(64, 0, msg);

  _display->display();
}

void SSD1306_OLEDDisplay_Mux::writeSmall(String msg) {
  _display->init();
  _display->clear();
  _display->flipScreenVertically();
  _display->setTextAlignment(TEXT_ALIGN_CENTER);
  _display->setFont(Arimo_Regular_20);

  _display->drawString(64, 4, msg);

  _display->display();
}

void SSD1306_OLEDDisplay_Mux::disable() {
    _enabled = false;
    _display->init();
    _display->clear();
    _display->displayOff();
}

void SSD1306_OLEDDisplay_Mux::enable() {
  if (!_enabled) {
    _enabled = true;
    _display->displayOn();
  }
}
