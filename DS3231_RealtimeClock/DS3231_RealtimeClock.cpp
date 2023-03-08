/*  Copyright (c) 2020-2023, Collab
 *  All rights reserved
*/
/*
  DS3231_RealtimeClock.cpp - Read and write to a DS3231 realtime clock.
*/
#include "DS3231_RealtimeClock.h"

DS3231_RealtimeClock::DS3231_RealtimeClock(TwoWire* wire, uint8_t eeprom_address) {
  _wire = wire;

  // storage
  _storage = new AT24C32_EEPROM(eeprom_address, wire);

  // rtc
  _rtc = new RTC_DS3231();
}

void DS3231_RealtimeClock::begin() {
  // initializing the rtc
  if (!_rtc->begin(_wire)) {
    Log.warning(F("Initializing DS3231... Error!" CR));
  }

  if (_rtc->lostPower()) {
    // when time needs to be set on a new device, or after a battery power
    // loss, the following line sets the RTC to the date and time this
    // project was compiled
    _rtc->adjust(DateTime(F(__DATE__), F(__TIME__)));

    // fix offset
    //adjust(now().unixtime() + (60 * 60));

    Log.info(F("DS3231: updated time." CR));
  }

  // store and print startup datetime
  startupTime = now();

  // set current temperature
  startupTemperature = getTemperature();
}

DateTime DS3231_RealtimeClock::now() {
  return _rtc->now();
}

void DS3231_RealtimeClock::adjust(unsigned long actualTime) {
  // check if it's a meaningful value in the future
  if (actualTime > 1611178509) {
    Log.info(F("Synced time:\t%s" CR),
      formatDateTime(DateTime(actualTime))
    );

    // update rtc
    _rtc->adjust(DateTime(actualTime));
  }
}

DateTime DS3231_RealtimeClock::load(int address) {
  int addr = address;
  char data[16];
  byte b = _storage->read_byte(addr);

  while (b != 0) {
    data[addr] = (char)b;
    addr++;
    // access an address from the memory
    b = _storage->read_byte(addr);
  }

  uint32_t timestamp = atol(data);

  return DateTime(SECONDS_FROM_1970_TO_2000 + timestamp);
}

void DS3231_RealtimeClock::save(DateTime timestamp, int address) {
  int addr = address;

  // store the timestamp
  uint32_t sec = timestamp.secondstime();
  char data[16];
  itoa(sec, data, 10);

  // write to EEPROM memory
  _storage->write_page(addr, (byte *)data, sizeof(data));
}

String DS3231_RealtimeClock::getStartupTime() {
  return formatDateTime(startupTime);
}

String DS3231_RealtimeClock::formatTime(DateTime dt) {
  return dt.timestamp(DateTime::TIMESTAMP_TIME);
}

String DS3231_RealtimeClock::formatDate(DateTime dt) {
  return dt.timestamp(DateTime::TIMESTAMP_DATE);
}

String DS3231_RealtimeClock::formatDateTime(DateTime dt) {
  return formatDate(dt) + " " + formatTime(dt);
}

float DS3231_RealtimeClock::getTemperature() {
  return _rtc->getTemperature();
}
