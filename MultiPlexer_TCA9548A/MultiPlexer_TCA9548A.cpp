/*
  MultiPlexer_TCA9548A.h - Control TCA9548A I2C multiplexer.
*/

#include "MultiPlexer_TCA9548A.h"

MultiPlexer_TCA9548A::MultiPlexer_TCA9548A(int i2c_addr) {
  _mux = new TCA9548A(i2c_addr);
}

void MultiPlexer_TCA9548A::begin() {
  _mux->begin(Wire);             // TwoWire instance can be passed here as 3rd argument
  _mux->closeAll();              // Set a base state which we know (also the default state on power on)
  changeBus(0);          // tell the TCA9548A we want to use I2C bus number zero (to talk to the OLED)
}

void MultiPlexer_TCA9548A::changeBus(uint8_t bus_nr) {
  _mux->openChannel(bus_nr);
}
