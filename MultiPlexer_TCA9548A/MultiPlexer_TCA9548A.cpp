/*
  MultiPlexer_TCA9548A.h - Control TCA9548A I2C multiplexer.
*/

#include "MultiPlexer_TCA9548A.h"

TwoWire twire = TwoWire(1);

MultiPlexer_TCA9548A::MultiPlexer_TCA9548A(int i2c_addr) {
  _mux = new TCA9548A(i2c_addr);
}

void MultiPlexer_TCA9548A::begin(int sda_pin, int scl_pin) {
  _mux->begin(twire, sda_pin, scl_pin);

  // set a base state which we know (also the default state on power on)
  _mux->closeAll();
}

void MultiPlexer_TCA9548A::openChannel(uint8_t channel_nr) {
  _mux->openChannel(channel_nr);
}

void MultiPlexer_TCA9548A::closeChannel(uint8_t channel_nr) {
  _mux->closeChannel(channel_nr);
}

