/*  Copyright (c) 2020-2021, Collab
 *  All rights reserved
*/
/*
  MultiPlexer_PCF8574.h
*/
#ifndef MultiPlexer_PCF8574_h
#define MultiPlexer_PCF8574_h

#include <Arduino.h>
#include <Method.h>
#include <PCF8574.h>

class MultiPlexer_PCF8574
{
  public:
    MultiPlexer_PCF8574(uint8_t address, uint8_t sda, uint8_t scl);
    void begin();
    void digitalWrite(uint8_t pin, uint8_t value);
    uint8_t digitalRead(uint8_t pin);

  private:
    PCF8574* _expander;
    uint8_t _sdaPin;
    uint8_t _sclPin;
};

#endif
