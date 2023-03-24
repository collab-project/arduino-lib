/*  Copyright (c) 2020-2023, Collab
 *  All rights reserved
*/
/*
  MultiPlexer_PCF8574.h
*/
#ifndef MultiPlexer_PCF8574_h
#define MultiPlexer_PCF8574_h

#include <Arduino.h>
#include <PCF8574.h>
#include <ArduinoLog.h>

class MultiPlexer_PCF8574
{
  public:
    MultiPlexer_PCF8574(uint8_t address, TwoWire* wire = &Wire);
    bool begin(uint8_t value = LOW);
    bool isConnected();
    void digitalWrite(uint8_t pin, uint8_t value);
    uint8_t digitalRead(uint8_t pin);

  private:
    PCF8574* _expander;
};

#endif
