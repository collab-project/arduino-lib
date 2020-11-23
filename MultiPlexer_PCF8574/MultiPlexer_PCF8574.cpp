/*
  MultiPlexer_PCF8574.cpp
*/

#include <MultiPlexer_PCF8574.h>

MultiPlexer_PCF8574::MultiPlexer_PCF8574(uint8_t address) {
  _expander = new PCF8574(address);
}

void MultiPlexer_PCF8574::begin() {
  for (int i=0; i<8; i++) {
    _expander->pinMode(i, INPUT);
  }

	if (_expander->begin()) {
		Serial.println("OK");
	} else{
		Serial.println("KO");
	}
}

void MultiPlexer_PCF8574::loop() {
}
