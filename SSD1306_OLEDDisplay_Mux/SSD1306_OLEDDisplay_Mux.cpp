/*  Copyright (c) 2021-2023, Collab
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
  if (_flipVertical == true) {
    _display->flipScreenVertically();
  }
  setTextAlignment(TEXT_ALIGN_CENTER);
  _display->setFont(Arimo_Regular_30);

  _expander->closeChannel(_expanderChannel);
}

void SSD1306_OLEDDisplay_Mux::drawImage(
  int16_t xMove, int16_t yMove, int16_t width, int16_t height,
  const uint8_t *xbm, bool clear_display
) {
  _expander->openChannel(_expanderChannel);

  if (clear_display) {
    _display->clear();
  }
  _display->drawXbm(xMove, yMove, width, height, xbm);
  _display->display();

  _expander->closeChannel(_expanderChannel);
}

void SSD1306_OLEDDisplay_Mux::writeBig(String msg, int16_t x, int16_t y, bool clear_display) {
  _expander->openChannel(_expanderChannel);

  if (clear_display) {
    _display->clear();
  }
  _display->setFont(Arimo_Regular_30);

  _display->drawString(x, y, msg);
  _display->display();

  _expander->closeChannel(_expanderChannel);
}

void SSD1306_OLEDDisplay_Mux::writeTiny(String msg, int16_t x, int16_t y, bool clear_display) {
  _expander->openChannel(_expanderChannel);

  if (clear_display) {
    _display->clear();
  }
  _display->setFont(Arimo_Regular_16);

  _display->drawString(x, y, msg);
  _display->display();

  _expander->closeChannel(_expanderChannel);
}

void SSD1306_OLEDDisplay_Mux::writeSmall(String msg, int16_t x, int16_t y, bool clear_display) {
  _expander->openChannel(_expanderChannel);

  if (clear_display) {
    _display->clear();
  }
  _display->setFont(Arimo_Regular_20);

  _display->drawString(x, y, msg);
  _display->display();

  _expander->closeChannel(_expanderChannel);
}

void SSD1306_OLEDDisplay_Mux::setTextAlignment(OLEDDISPLAY_TEXT_ALIGNMENT textAlignment) {
  _display->setTextAlignment(textAlignment);
}

void SSD1306_OLEDDisplay_Mux::disable() {
  _expander->openChannel(_expanderChannel);

  _enabled = false;
  _display->clear();
  _display->display();
  _display->displayOff();

  _expander->closeChannel(_expanderChannel);
}

void SSD1306_OLEDDisplay_Mux::enable() {
  if (!_enabled) {
    _enabled = true;

    _expander->openChannel(_expanderChannel);

    _display->displayOn();

    _expander->closeChannel(_expanderChannel);
  }
}
