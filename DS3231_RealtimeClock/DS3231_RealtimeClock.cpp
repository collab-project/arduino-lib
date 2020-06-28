/*
  DS3231_RealtimeClock.cpp - Read and write to a DS3231 realtime clock.
*/
#include "DS3231_RealtimeClock.h"

#define countof(a) (sizeof(a) / sizeof(a[0]))

void printDateTime(const RtcDateTime& dt) {
  char datestring[20];

  snprintf_P(datestring,
    countof(datestring),
    PSTR("%04u/%02u/%02u %02u:%02u:%02u"),
    dt.Year(),
    dt.Month(),
    dt.Day(),
    dt.Hour(),
    dt.Minute(),
    dt.Second()
  );
  Serial.print(datestring);
}

DS3231_RealtimeClock::DS3231_RealtimeClock(int scl_pin, int sda_pin) {
  _sclPin = scl_pin;
  _sdaPin = sda_pin;

  _rtc = new RtcDS3231<TwoWire>(Wire);
}

void DS3231_RealtimeClock::begin() {
  // initialize rtc
  _rtc->Begin(_sdaPin, _sclPin);

  RtcDateTime build_date = getBuildDate();
  Serial.print("Build date: ");
  printDateTime(build_date);
  Serial.println();

  if (!_rtc->IsDateTimeValid()) {
    if (_rtc->LastError() != 0) {
      // we have a communications error
      // see https://www.arduino.cc/en/Reference/WireEndTransmission for 
      // what the number means
      Serial.print("RTC communications error = ");
            Serial.println(_rtc->LastError());
        }
        else
        {
            // Common Causes:
            //    1) first time you ran and the device wasn't running yet
            //    2) the battery on the device is low or even missing
            Serial.println("RTC lost confidence in the DateTime!");

            // following line sets the RTC to the date & time this sketch was compiled
            // it will also reset the valid flag internally unless the Rtc device is
            // having an issue
            _rtc->SetDateTime(build_date);
        }
    }

    if (!_rtc->GetIsRunning()) {
      activate();
    }

    // print current time
    startupTime = getDateTime();
    Serial.print("Local time: ");
    printDateTime(startupTime);
    Serial.println();

    // set current temperature
    startupTemperature = getTemperature();
}

void DS3231_RealtimeClock::loop() {
}

void DS3231_RealtimeClock::activate() {
  Serial.println("RTC was not actively running, starting now");

  _rtc->SetIsRunning(true);
}

RtcDateTime DS3231_RealtimeClock::getDateTime() {
  if (!_rtc->GetIsRunning()) {
    activate();
  }
  // never assume the Rtc was last configured by you, so
  // just clear them to your needed state
  _rtc->Enable32kHzPin(false);
  _rtc->SetSquareWavePin(DS3231SquareWavePin_ModeNone);

  return _rtc->GetDateTime();
}

void DS3231_RealtimeClock::update(RtcDateTime new_dt) {
  if (!_rtc->GetIsRunning()) {
    activate();
  }
  Serial.print("Setting RTC time to: ");
  printDateTime(new_dt);
  Serial.println();

  _rtc->SetDateTime(new_dt);

  Serial.print("RTC time now: ");
  printDateTime(getDateTime());
  Serial.println();
}

RtcDateTime DS3231_RealtimeClock::getBuildDate() {
  return RtcDateTime(__DATE__, __TIME__);
}

float DS3231_RealtimeClock::getTemperature() {
  if (!_rtc->GetIsRunning()) {
    activate();
  }
  RtcTemperature temp = _rtc->GetTemperature();

  return temp.AsFloatDegC();
}
