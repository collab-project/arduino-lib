/*
  MultiPlexer_74HC4067.cpp
*/

#include "MultiPlexer_74HC4067.h"

MultiPlexer_74HC4067::MultiPlexer_74HC4067(
  uint8_t signal_pin,
  uint8_t select0_pin,
  int8_t select1_pin,
  int8_t select2_pin,
  int8_t select3_pin,
  uint8_t signal_mode,
  uint8_t signal_type
) {
  _mux = new Type4067Mux(
    signal_pin,
    signal_mode,
    signal_type,
    select0_pin,
    select1_pin,
    select2_pin,
    select3_pin
  );
}

int MultiPlexer_74HC4067::read(byte channel) {
  return _mux->read(channel);
}
