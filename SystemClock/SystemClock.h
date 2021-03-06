/*  Copyright (c) 2020-2021, Collab
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
        int scl_pin,
        int sda_pin,
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
    DateTime startupTime;

  private:
    char* _ntpServer;
    long _gmtOffset_sec;
    int _daylightOffset_sec;
    DS3231_RealtimeClock* _clock;

    String formatTime(DateTime dt);
};

#endif