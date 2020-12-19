/*  Copyright (c) 2020, Collab
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
    MultiPlexer_PCF8574(uint8_t address);
    void begin();
    void loop();
    void pinMode(uint8_t pin, uint8_t mode, uint8_t initialValue = HIGH);
    void digitalWrite(uint8_t pin, uint8_t value);

  private:
    PCF8574* _expander;
};

#endif
