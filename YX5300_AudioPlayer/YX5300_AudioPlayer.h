/*
  YX5300_AudioPlayer.h - Control YX5300 audio player.
*/
#ifndef YX5300_AudioPlayer_h
#define YX5300_AudioPlayer_h

#define USE_SOFTWARESERIAL 0

#include <Arduino.h>
#include <MD_YX5300.h>

class YX5300_AudioPlayer
{
  public:
    YX5300_AudioPlayer(short rx_pin, short tx_pin, int volume = 10);
    void begin();
    void loop();

  private:
    MD_YX5300* _player;
    int _volume;

    const uint8_t PLAY_FOLDER = 1;
};

#endif