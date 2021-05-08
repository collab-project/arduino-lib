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
#include <Method.h>
#include <MD_YX5300.h>

#if USE_SOFTWARESERIAL
#include <SoftwareSerial.h>
#endif

class YX5300_AudioPlayer {
  public:
    YX5300_AudioPlayer(
      short rx_pin,
      short tx_pin,
      Method ready_callback,
      uint8_t volume = 10,
      uint32_t timeout = 200
    );
    void begin();
    void loop();
    void stop();
    void nextTrack();
    void prevTrack();
    void playStart();
    void playSpecific(uint8_t folder, uint8_t track);
    void playFolderRepeat(uint8_t folder = 1);
    void playFolderShuffle(uint8_t folder = 1);
    void mute();
    void unmute();
    void wakeUp();
    void sleep();
    void setTimeout(uint32_t timeout = 200);
    void setVolume(uint8_t volume);
    uint8_t getMaxVolume();
    void queryFile();
    void queryStatus();
    void queryFolderCount();
    void queryFolderFiles(uint8_t folder);

    uint32_t totalFolders;
    uint32_t currentFolderIndex;
    uint32_t currentTrackIndex;

  private:
    uint8_t _volume;
    uint32_t _timeOut;
    bool _fileEnded = false;
    bool _shuffleEnabled = false;
    Method _readyCallback;
    std::vector<int> _folders;
    std::vector<int> _playList;

    MD_YX5300 *_player;
    SoftwareSerial *_stream;

    int getRandomTrack(int totalTracks);

    // callbacks
    void onFileEnded();
    void onPlayerCallback();
    void onFilesFolder(int total);
    void onTotalFolders(int total);
};

#endif