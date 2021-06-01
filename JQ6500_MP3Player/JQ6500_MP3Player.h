/*  Copyright (c) 2020-2021, Collab
 *  All rights reserved
*/
/*
  JQ6500_MP3Player.h - Control JQ6500 MP3 player.
*/
#ifndef JQ6500_MP3Player_h
#define JQ6500_MP3Player_h

#include <Arduino.h>
#include <JQ6500_Serial.h>

#if defined(__AVR__) || defined(ESP8266)
#include <SoftwareSerial.h>
#endif

class JQ6500_MP3Player
{
  public:
    #if defined(__AVR__) || defined(ESP8266)
    JQ6500_MP3Player(
      SoftwareSerial * serial,
      int initial_volume = -1,
      int source = MP3_SRC_SDCARD,
      long baud_rate = 9600
    );
    #elif defined(ESP32)
    JQ6500_MP3Player(
      HardwareSerial * serial,
      int initial_volume = -1,
      int source = MP3_SRC_SDCARD,
      long baud_rate = 9600
    );
    #endif
    void begin();
    void loop();

    // general
    void reset();
    byte getStatus();
    void setSource(int source);

    // loop
    int loopMode;
    int getLoopMode();
    void setLoopMode(int mode);

    // position
    char currentFileName[4];
    void getCurrentFileName();
    unsigned int currentFileIndex(byte source = MP3_SRC_SDCARD);
    unsigned int currentFileLength();
    unsigned int currentFilePosition();
    unsigned int getTotalFiles(byte source = MP3_SRC_SDCARD);
    unsigned int getTotalFolders(byte source = MP3_SRC_SDCARD);
    unsigned int totalSDFiles;
    unsigned int totalSDFolders;

    // playback
    void play();
    void pause();
    void nextTrack();
    void nextFolder();
    void previousTrack();
    void previousFolder();
    void playSpecific(unsigned int folder, unsigned int track);

    // volume
    int volume;
    int getVolume();
    int volumeUp();
    int volumeDown();
    void setVolume(int newVolume);

    // equalizer
    int equalizerMode;
    int getEqualizer();
    void setEqualizer(int mode);

  private:
    Stream * _serial;
    JQ6500_Serial* _player;

    const int _minVolume = 0;
    const int _maxVolume = 30;

    int _source;
    long _baudRate;
    bool _hwSerial;
};

#endif