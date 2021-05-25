/*  Copyright (c) 2020, Collab
 *  All rights reserved
*/
/*
  JQ6500_MP3Player.h - Control JQ6500 MP3 player.
*/
#ifndef JQ6500_MP3Player_h
#define JQ6500_MP3Player_h

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <JQ6500_Serial.h>

class JQ6500_MP3Player
{
  public:
    JQ6500_MP3Player(
      short rx_pin,
      short tx_pin,
      int volume = 10,
      int source = MP3_SRC_SDCARD,
      long baud_rate = 9600
    );
    void begin();
    void loop();

    byte getStatus();
    int getVolume();
    void setVolume(int volume);
    void setSource(int source);
    int getEqualizer();
    void setEqualizer(int equalizerMode);
    unsigned int getTotalFiles(int source);
    void playSpecific(unsigned int folder, unsigned int track);

  private:
    JQ6500_Serial* _player;
    long _baudRate;
    int _volume;
    int _source;
    int _equalizerMode;
};

#endif