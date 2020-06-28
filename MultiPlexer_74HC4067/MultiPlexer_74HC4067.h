/*
  MultiPlexer_74HC4067.h
*/
#ifndef MultiPlexer_74HC4067_h
#define MultiPlexer_74HC4067_h

#include <Arduino.h>
#include <Type4067Mux.h>

class MultiPlexer_74HC4067 {
  public:
    MultiPlexer_74HC4067(
      uint8_t signal_pin,
      uint8_t select0_pin,
      int8_t select1_pin,
      int8_t select2_pin,
      int8_t select3_pin,
      uint8_t signal_mode = INPUT,
      uint8_t signal_type = ANALOG_TYPE
    );
    int read(byte channel);

  private:
    Type4067Mux* _mux;
};

#endif