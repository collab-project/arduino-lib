/*  Copyright (c) 2021-2023, Collab
 *  All rights reserved
*/
/*
  SSD1306_OLEDDisplay_Mux.cpp - Control SSD1306 OLED display using TCA9548A expander.
*/
#ifndef SSD1306_OLEDDisplay_Mux_h
#define SSD1306_OLEDDisplay_Mux_h

#include <Arduino.h>
#include <Wire.h>
#include <SSD1306Wire.h>
#include <MultiPlexer_TCA9548A.h>
#include <SSD1306_OLEDDisplay_Mux_Fonts.h>

class SSD1306_OLEDDisplay_Mux {
  public:
    SSD1306_OLEDDisplay_Mux(
      MultiPlexer_TCA9548A* expander,
      uint8_t expander_channel = 0,
      uint8_t address = 0x3C,
      bool flip_vertical = false,
      OLEDDISPLAY_GEOMETRY size = GEOMETRY_128_32,
      HW_I2C bus = I2C_TWO
    );
    void begin();
    void loop();
    void disable();
    void enable();
    void writeBig(String msg);
    void writeSmall(String msg);

  private:
    uint8_t _address;
    uint8_t _expanderChannel;
    bool _flipVertical;
    bool _enabled = false;

    SSD1306Wire* _display;
    MultiPlexer_TCA9548A* _expander;
};

#endif