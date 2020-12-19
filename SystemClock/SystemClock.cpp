/*  Copyright (c) 2020, Collab
 *  All rights reserved
*/
/*
  SystemClock.cpp
*/

#include "SystemClock.h"

/**
 * Constructor.
 *
 * @param ntp_server
 * @param gmtOffset_sec
 * @param daylightOffset_sec
 */
SystemClock::SystemClock(
  int scl_pin,
  int sda_pin,
  char* ntp_server,
  long int gmtOffset_sec,
  int daylightOffset_sec
) {
  _ntpServer = ntp_server;
  _gmtOffset_sec = gmtOffset_sec;
  _daylightOffset_sec = daylightOffset_sec;

  _clock = new DS3231_RealtimeClock(scl_pin, sda_pin);
}

void SystemClock::begin() {
  _clock->begin();

  startupTime = _clock->startupTime;
}

void SystemClock::sync() {
  Serial.print("Syncing time with ");
  Serial.println(_ntpServer);
  Serial.println();

  configTime(_gmtOffset_sec, _daylightOffset_sec, _ntpServer);

  setLocalTime();
}

void SystemClock::setLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time from NTP");
    return;
  }

  // sync realtime clock
  RtcDateTime new_dt(
    timeinfo.tm_year + 1900,
    timeinfo.tm_mon + 1,
    timeinfo.tm_mday,
    timeinfo.tm_hour,
    timeinfo.tm_min,
    timeinfo.tm_sec
  );
  _clock->update(new_dt);

  Serial.println("Local time: ");
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  Serial.println("===============================");
}

float SystemClock::getStartupTemperature() {
  return _clock->startupTemperature;
}

String SystemClock::getTime() {
  RtcDateTime dt = _clock->getDateTime();
  return formatTime(dt);
}

String SystemClock::getStartupTime() {
  return formatTime(startupTime);
}

String SystemClock::formatTime(RtcDateTime dt) {
  char tstamp[9];

  snprintf_P(tstamp,
    countof(tstamp),
    PSTR("%02u:%02u:%02u"),
    dt.Hour(),
    dt.Minute(),
    dt.Second()
  );

  return tstamp;
}
