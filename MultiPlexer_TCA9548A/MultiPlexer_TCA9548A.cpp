/*  Copyright (c) 2021-2023, Collab
 *  All rights reserved
*/
/*
  MultiPlexer_TCA9548A.h - Control TCA9548A I2C multiplexer.
*/

#include <MultiPlexer_TCA9548A.h>

MultiPlexer_TCA9548A::MultiPlexer_TCA9548A(int i2c_addr) {
  _address = i2c_addr;
  _mux = new TCA9548A(i2c_addr);
}

void MultiPlexer_TCA9548A::begin() {
  // XXX: don't hardcode Wire instance
  _mux->begin(Wire1);

  // set a base state which we know (also the default state on power on)
  _mux->closeAll();
}

void MultiPlexer_TCA9548A::switchChannel(uint8_t channel_nr) {
  closeAll();
  openChannel(channel_nr);
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

void MultiPlexer_TCA9548A::scan(bool ignoreMultiplexer) {
  byte error, address;
  int nDevices = 0;

  for (address = 1; address < 127; address++) {
    Wire1.beginTransmission(address);
    error = Wire1.endTransmission();
    if (error == 0) {
      if (!(ignoreMultiplexer && address == _address)) {
        if (address < 16) {
          Log.info(F("TCA9548A - I2C device found at address 0x0%x" CR), address);
        } else {
          Log.info(F("TCA9548A - I2C device found at address 0x%x" CR), address);
        }
        nDevices++;
      }
    } else if (error == 4) {
      if (address < 16) {
        Log.info(F("TCA9548A - Unknown error at address 0x0%x" CR), address);
      } else {
        Log.info(F("TCA9548A - Unknown error at address 0x%x" CR), address);
      }
    }
  }

  if (nDevices == 0) {
    Log.warning(F("TCA9548A - No I2C devices found" CR));
  }
}

void MultiPlexer_TCA9548A::scanAll() {
  // see https://github.com/WifWaf/TCA9548A/issues/6
  for (int channel = 0; channel < 8; channel++) {

  }
}
