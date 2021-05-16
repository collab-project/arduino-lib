/*  Copyright (c) 2021, Collab
 *  All rights reserved
*/
/*
  SSD1306_OLEDDisplay_Mux.cpp - Control SSD1306 OLED display using TCA9548A expander.
*/
#ifndef SSD1306_OLEDDisplay_Mux_h
#define SSD1306_OLEDDisplay_Mux_h

#include <Arduino.h>
#include <SSD1306Wire.h>
#include <SSD1306_OLEDDisplay_Mux_Fonts.h>

class SSD1306_OLEDDisplay_Mux {
  public:
    SSD1306_OLEDDisplay_Mux(int sda_pin, int scl_pin, uint8_t address = 0x3C);
    void begin();
    void loop();
    void disable();
    void enable();
    void writeBig(String msg);
    void writeSmall(String msg);

  private:
    int _sdaPin;
    int _sclPin;
    uint8_t _address;
    SSD1306Wire* _display;
    bool _enabled = false;
};

#endif