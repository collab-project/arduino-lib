/*  Copyright (c) 2022-2023, Collab
 *  All rights reserved
*/
/*
  KY006_Buzzer_ESP32.cpp - Control KY-006 piezo buzzer connected
  to a digital pin on a ESP32.
*/

#include "KY006_Buzzer_ESP32.h"

KY006_Buzzer_ESP32::KY006_Buzzer_ESP32(int buzzer_pin, int channel) {
  _buzzerPin = buzzer_pin;
  _channel = channel;
}

void KY006_Buzzer_ESP32::begin() {
}

void KY006_Buzzer_ESP32::enable(note_t frequency, unsigned long duration) {
  ledcAttachPin(_buzzerPin, _channel);
  ledcWriteNote(_channel, frequency, duration);
  delay(duration);

  disable();
}

void KY006_Buzzer_ESP32::disable() {
  ledcDetachPin(_buzzerPin);
}
