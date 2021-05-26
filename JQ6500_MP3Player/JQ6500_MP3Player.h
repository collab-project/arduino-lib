/*  Copyright (c) 2020-2021, Collab
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

    // general
    void reset();
    byte getStatus();
    unsigned int getTotalFiles(byte source = MP3_SRC_SDCARD);
    unsigned int getTotalFolders(byte source = MP3_SRC_SDCARD);
    void setSource(int source);
    int getLoopMode();
    void setLoopMode(int loopMode);

    // playback
    void play();
    void pause();
    void nextTrack();
    void nextFolder();
    void previousTrack();
    void previousFolder();
    void playSpecific(unsigned int folder, unsigned int track);

    // volume
    int getVolume();
    void setVolume(int volume);
    void volumeUp();
    void volumeDown();

    // equalizer
    int getEqualizer();
    void setEqualizer(int equalizerMode);

  private:
    JQ6500_Serial* _player;

    int _volume;
    int _source;
    long _baudRate;
    int _loopMode;
    int _equalizerMode;
};

#endif