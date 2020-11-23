/*
  MultiPlexer_PCF8574.cpp
*/

#include <MultiPlexer_PCF8574.h>

MultiPlexer_PCF8574::MultiPlexer_PCF8574(uint8_t address) {
  _expander = new PCF8574(address);
}

void MultiPlexer_PCF8574::begin() {
  Serial.print("Initializing PCF8574... ");
  // inputs
  int i = 0;
  for (i = 0; i<4; i++) {
    _expander->pinMode(i, INPUT);
  }
  // outputs
  for (i=4; i<8; i++) {
    _expander->pinMode(i, OUTPUT, LOW);
  }

  if (_expander->begin()) {
    Serial.println("OK");
  } else{
    Serial.println("Error!");
  }
}

void MultiPlexer_PCF8574::loop() {
}
