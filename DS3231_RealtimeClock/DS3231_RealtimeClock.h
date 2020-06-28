/*
  DS3231_RealtimeClock.h - Read and write to a DS3231 realtime clock.
*/
#ifndef DS3231_RealtimeClock_h
#define DS3231_RealtimeClock_h

#include "Arduino.h"
#include <Wire.h>
#include <RtcDS3231.h>

class DS3231_RealtimeClock
{
  public:
    DS3231_RealtimeClock() {};
    DS3231_RealtimeClock(
      int scl_pin,
      int sda_pin
    );
    void begin();
    void loop();
    void activate();
    float getTemperature();
    RtcDateTime getDateTime();
    RtcDateTime getBuildDate();
    void update(RtcDateTime new_dt);
    RtcDateTime startupTime;
    float startupTemperature;

  private:
    RtcDS3231<TwoWire>* _rtc;
    int _sclPin;
    int _sdaPin;
};

#endif