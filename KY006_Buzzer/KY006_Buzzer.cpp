/*  Copyright (c) 2021, Collab
 *  All rights reserved
*/
/*
  KY006_Buzzer.cpp - Control KY-006 passive piezo buzzer.
*/

#include "KY006_Buzzer.h"

KY006_Buzzer::KY006_Buzzer(int buzzer_pin) {
  _buzzerPin = buzzer_pin;
}

void KY006_Buzzer::begin() {
  pinMode(_buzzerPin, OUTPUT);
}

void KY006_Buzzer::enable(unsigned int frequency, unsigned long duration) {
  // stop sound first
  disable();

  // start sound
  tone(_buzzerPin, frequency, duration);
}

void KY006_Buzzer::disable() {
  noTone(_buzzerPin);
}
