/*  Copyright (c) 2020-2021, Collab
 *  All rights reserved
*/
/*
  YX5300_AudioPlayer.h - Control YX5300 audio player.
*/
#ifndef YX5300_AudioPlayer_h
#define YX5300_AudioPlayer_h

#ifndef USE_SOFTWARESERIAL
// Set to 1 to use SoftwareSerial library, 0 for native serial port
#define USE_SOFTWARESERIAL 1
#endif

#include <Arduino.h>
#include <MD_YX5300.h>

#if USE_SOFTWARESERIAL
#include <SoftwareSerial.h>
#endif

class YX5300_AudioPlayer {
  public:
    YX5300_AudioPlayer(
        short rx_pin,
        short tx_pin,
        int volume = 10
    );
    void begin();
    void loop();
    void query();
    void playFolderRepeat(uint8_t folder = 1);

  private:
    int _volume;

    SoftwareSerial *_stream;
    MD_YX5300 *_player;
};

#endif