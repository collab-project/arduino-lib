/*  Copyright (c) 2021, Collab
 *  All rights reserved
*/
/*
  SSD1306_OLEDDisplay_Mux.cpp - Control SSD1306 OLED display using TCA9548A expander.
*/

#include <SSD1306_OLEDDisplay_Mux.h>

SSD1306_OLEDDisplay_Mux::SSD1306_OLEDDisplay_Mux(
  MultiPlexer_TCA9548A* expander,
  uint8_t expander_channel,
  uint8_t address,
  bool flip_vertical,
  OLEDDISPLAY_GEOMETRY size,
  HW_I2C bus
) {
  _expander = expander;
  _expanderChannel = expander_channel;
  _address = address;
  _flipVertical = flip_vertical;

  _display = new SSD1306Wire(address, -1, -1, size, bus);
}

void SSD1306_OLEDDisplay_Mux::begin() {
  _expander->openChannel(_expanderChannel);

  _display->init();
  _display->clear();
  if (_flipVertical) {
    _display->flipScreenVertically();
  }
  _display->setTextAlignment(TEXT_ALIGN_CENTER);

  _expander->closeChannel(_expanderChannel);
}

void SSD1306_OLEDDisplay_Mux::writeBig(String msg) {
  _expander->openChannel(_expanderChannel);

  _display->clear();
  _display->setFont(Arimo_Regular_30);

  _display->drawString(64, 0, msg);
  _display->display();

  _expander->closeChannel(_expanderChannel);
}

void SSD1306_OLEDDisplay_Mux::writeSmall(String msg) {
  _expander->openChannel(_expanderChannel);

  _display->clear();
  _display->setFont(Arimo_Regular_20);

  _display->drawString(64, 4, msg);
  _display->display();

  _expander->closeChannel(_expanderChannel);
}

void SSD1306_OLEDDisplay_Mux::disable() {
    _enabled = false;
    _display->clear();
    _display->displayOff();
}

void SSD1306_OLEDDisplay_Mux::enable() {
  if (!_enabled) {
    _enabled = true;
    _display->displayOn();
  }
}
