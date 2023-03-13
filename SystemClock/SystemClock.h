/*  Copyright (c) 2020-2023, Collab
 *  All rights reserved
*/
/*
   SystemClock.h
*/
#ifndef SystemClock_h
#define SystemClock_h

#include <Arduino.h>
#include <RTClib.h>
#include <DS3231_RealtimeClock.h>

class SystemClock
{
  public:
    SystemClock(
        TwoWire* wire,
        char *ntpServer = "pool.ntp.org",
        long int gmtOffset_sec = 3600,
        int daylightOffset_sec = 3600
    );
    void sync();
    void begin();
    void setLocalTime();
    float getStartupTemperature();
    DateTime now();
    String getTime();
    String getStartupTime();
    String formatTime(DateTime dt);
    String formatDate(DateTime dt);
    String formatDateTime(DateTime dt);
    DateTime startupTime;

  private:
    char* _ntpServer;
    long _gmtOffset_sec;
    int _daylightOffset_sec;
    DS3231_RealtimeClock* _clock;
};

#endif