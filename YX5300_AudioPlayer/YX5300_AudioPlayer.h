/*  Copyright (c) 2020-2021, Collab
 *  All rights reserved
*/
/*
  YX5300_AudioPlayer.h - Control YX5300 audio player.
*/
#ifndef YX5300_AudioPlayer_h
#define YX5300_AudioPlayer_h

#include <Arduino.h>
#include <Method.h>
#include <MD_YX5300.h>
#include <ArduinoLog.h>

#if defined(__AVR__) || defined(ESP8266)
#include <SoftwareSerial.h>
#endif

struct Track {
  uint8_t index;
  uint8_t folder;
};

class YX5300_AudioPlayer {
  public:
    #if defined(__AVR__) || defined(ESP8266)
    YX5300_AudioPlayer(
      SoftwareSerial * serial,
      Method ready_callback,
      uint8_t volume = 10,
      uint32_t timeout = 200
    );
    #elif defined(ESP32)
    YX5300_AudioPlayer(
      HardwareSerial * serial,
      Method ready_callback,
      uint8_t volume = 10,
      uint32_t timeout = 200
    );
    #endif
    void begin();
    void loop();
    void stop();
    void nextTrack();
    void prevTrack();
    void playStart();
    void playShuffle();
    void playSpecific(uint8_t folder, uint8_t track);
    void playFolderRepeat(uint8_t folder = 1);
    void playFolderShuffle(uint8_t folder = 1);
    void mute();
    void unmute();
    void wakeUp();
    void sleep();
    void setTimeout(uint32_t timeout = 200);
    void setVolume(uint8_t volume);
    void setEqualizerMode(uint8_t mode);
    uint8_t getMaxVolume();
    void queryFile();
    void queryStatus();
    void queryEqualizer();
    void queryFolderCount();
    void queryFolderFiles(uint8_t folder = 1);

    int equalizerMode = 0;
    uint32_t totalFolders;
    Track currentTrack;

  private:
    bool _hwSerial;
    uint8_t _volume;
    uint32_t _timeOut;
    int _fileEnded = 0;
    bool _repeatEnabled = true;
    bool _shuffleEnabled = false;
    bool _shuffleAll = true;
    Method _readyCallback;
    std::vector<int> _folders;
    std::vector<Track> _playList;

    Stream * _stream;
    MD_YX5300 *_player;

    void setupCallbacks();
    Track getRandomTrack(uint8_t folder = 1);
    Track addTrack(uint8_t index, uint8_t folder);

    // callbacks
    void onPlayerCallback();
    void onFileEnded(int index);
    void onFilesFolder(int total);
    void onTotalFolders(int total);
    void onEqualizerMode(int mode);
};

#endif