
/*
  MultiPlexer_PCF8574.cpp
*/

#include <MultiPlexer_PCF8574.h>

// Function interrupt
bool keyPressed = false;

void keyPressedOnPCF8574(){
  Serial.println("keyPressedOnPCF8574");
  keyPressed = true;
}


MultiPlexer_PCF8574::MultiPlexer_PCF8574(uint8_t address, uint8_t interrupt_pin) {
  _expander = new PCF8574(address, interrupt_pin, keyPressedOnPCF8574);
}

void MultiPlexer_PCF8574::begin() {
  /*pinMode(ESP8266_INTERRUPTED_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ESP8266_INTERRUPTED_PIN), keyPressedOnPCF8574, FALLING);*/

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
