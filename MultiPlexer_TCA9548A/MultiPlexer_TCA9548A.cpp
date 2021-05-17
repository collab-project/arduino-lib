/*
  MultiPlexer_TCA9548A.h - Control TCA9548A I2C multiplexer.
*/

#include <MultiPlexer_TCA9548A.h>

TwoWire twire = TwoWire(1);

MultiPlexer_TCA9548A::MultiPlexer_TCA9548A(int sda_pin, int scl_pin, int i2c_addr) {
  sdaPin = sda_pin;
  sclPin = scl_pin;
  wireBus = twire;

  _mux = new TCA9548A(i2c_addr);
}

void MultiPlexer_TCA9548A::begin() {
  _mux->begin(wireBus, sdaPin, sclPin);

  // set a base state which we know (also the default state on power on)
  _mux->closeAll();
}

void MultiPlexer_TCA9548A::openChannel(uint8_t channel_nr) {
  _mux->openChannel(channel_nr);
}

void MultiPlexer_TCA9548A::closeChannel(uint8_t channel_nr) {
  _mux->closeChannel(channel_nr);
}

void MultiPlexer_TCA9548A::closeAll() {
  _mux->closeAll();
}

void MultiPlexer_TCA9548A::scan() {
  byte error, address;
  int nDevices;
  int delayTime = 5000;
  nDevices = 0;
  for (address = 1; address < 127; address++) {
    twire.beginTransmission(address);
    error = twire.endTransmission();
    if (error == 0) {
      Serial.print(F("I2C device found at address 0x"));
      if (address < 16) {
        Serial.print(F("0"));
      }
      Serial.println(address, HEX);
      nDevices++;
    }
    else if (error == 4) {
      Serial.print(F("Unknow error at address 0x"));
      if (address < 16) {
        Serial.print(F("0"));
      }
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0) {
    Serial.println(F("No I2C devices found\n"));
  }
  delay(delayTime);
}
