/*  Copyright (c) 2020-2023, Collab
 *  All rights reserved
*/
/*
  DS3231_RealtimeClock.h - Read and write to a DS3231 realtime clock.
*/
#ifndef DS3231_RealtimeClock_h
#define DS3231_RealtimeClock_h

#include <Arduino.h>
#include <Wire.h>
#include <RTClib.h>
#include <ArduinoLog.h>
#include <AT24C32_EEPROM.h>

#define LAST_RUN_ADDRESS 0

class DS3231_RealtimeClock
{
  public:
    DS3231_RealtimeClock(TwoWire* wire, uint8_t eeprom_address = 0x57);
    void begin();
    DateTime now();
    DateTime load(int address = 0);
    void save(DateTime timestamp, int address = 0);
    void adjust(unsigned long actualTime);
    String formatTime(DateTime dt);
    String formatDate(DateTime dt);
    String formatDateTime(DateTime dt);
    String getStartupTime();
    float getTemperature();

    DateTime startupTime;
    float startupTemperature;

  private:
    TwoWire *_wire;
    RTC_DS3231 *_rtc;
    AT24C32_EEPROM *_storage;
};

#endif