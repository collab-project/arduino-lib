/*  Copyright (c) 2020-2023, Collab
 *  All rights reserved
*/
/*
  SystemClock.cpp
*/

#include "SystemClock.h"

SystemClock::SystemClock(
    TwoWire* wire,
    char *ntp_server,
    long int gmtOffset_sec,
    int daylightOffset_sec)
{
  _ntpServer = ntp_server;
  _gmtOffset_sec = gmtOffset_sec;
  _daylightOffset_sec = daylightOffset_sec;

  _clock = new DS3231_RealtimeClock(wire);
}

void SystemClock::begin() {
  _clock->begin();

  startupTime = _clock->startupTime;
}

void SystemClock::sync() {
  /*
  Serial.print("Syncing time with ");
  Serial.println(_ntpServer);
  Serial.println();

  configTime(_gmtOffset_sec, _daylightOffset_sec, _ntpServer);

  setLocalTime();
  */
}

void SystemClock::setLocalTime() {
  /*
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
  */
}

float SystemClock::getStartupTemperature() {
  return _clock->startupTemperature;
}

DateTime SystemClock::now() {
  return _clock->now();
}

String SystemClock::getTime() {
  DateTime dt = now();
  return formatTime(dt);
}

String SystemClock::getStartupTime() {
  return formatTime(startupTime);
}

String SystemClock::formatTime(DateTime dt) {
    return _clock->formatTime(dt);
}

String SystemClock::formatDate(DateTime dt) {
    return _clock->formatDate(dt);
}

String SystemClock::formatDateTime(DateTime dt) {
    return _clock->formatDateTime(dt);
}
