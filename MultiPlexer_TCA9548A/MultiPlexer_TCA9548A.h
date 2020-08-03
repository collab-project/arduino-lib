/*
  MultiPlexer_TCA9548A.h - Control TCA9548A I2C multiplexer.
*/
#ifndef MultiPlexer_TCA9548A_h
#define MultiPlexer_TCA9548A_h

#include <Arduino.h>
#include <Wire.h>
#include <TCA9548A.h>

class MultiPlexer_TCA9548A
{
  public:
    MultiPlexer_TCA9548A(int i2c_addr = 0x70);
    void begin();
    void changeBus(uint8_t bus_nr);

  private:
    TCA9548A* _mux;
};

#endif
