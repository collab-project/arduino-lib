/*  Copyright (c) 2020-2021, Collab
 *  All rights reserved
*/
/*
  JQ6500_MP3Player.cpp - Control JQ6500 MP3 player.
*/

#include <JQ6500_MP3Player.h>

#if defined(ESP32)
JQ6500_MP3Player::JQ6500_MP3Player(
  HardwareSerial * serial,
  int initial_volume,
  int source,
  long baud_rate
) {
  _hwSerial = true;
  _serial = serial;
  _source = source;
  _baudRate = baud_rate;

  volume = initial_volume;

  _player = new JQ6500_Serial(_serial);
}
#endif

#if defined(__AVR__) || defined(ESP8266)
JQ6500_MP3Player::JQ6500_MP3Player(
  SoftwareSerial * serial,
  int initial_volume,
  int source,
  long baud_rate
) {
  _hwSerial = false;
  _serial = serial;
  _source = source;
  _baudRate = baud_rate;

  volume = initial_volume;

  _player = new JQ6500_Serial(_serial);
}
#endif

/**
 * Setup device.
 */
void JQ6500_MP3Player::begin() {
  // start serial
  #if defined(__AVR__) || defined(ESP8266)
  static_cast<SoftwareSerial*>(_serial)->begin(_baudRate);
  #else
  static_cast<HardwareSerial*>(_serial)->begin(_baudRate);
  #endif

  m = millis();

  // reset device
  reset();
  setSource(_source);

  // set default loopmode
  setLoopMode(MP3_LOOP_ALL);

  getEqualizer();
  getLoopMode();

  // position
  totalSDFolders = getTotalFolders();
  totalSDFiles = getTotalFiles();
  getCurrentFileName();

  // volume
  // Note: do this as last call, otherwise it won't be
  // properly set...
  if (volume != -1) {
    // override volume
    setVolume(volume);
  } else {
    // get last volume
    getVolume();
  }
}

void JQ6500_MP3Player::loop() {
  // XXX: only do check if playback is active (determine manually)
  // XXX: fire event when currentFileName changed
  if (m < (millis() - _waitTime)) {
    // avoid getStatus, it's slow!
    //if ((getStatus() == MP3_STATUS_PLAYING)) {
      Serial.print(F("Current File: "));
      getCurrentFileName();
      Serial.println(currentFileName);
    //}
    m = millis();
  }
}

/**
 * Start playback.
 */
void JQ6500_MP3Player::play() {
  _player->play();
}

/**
 * Pause playback.
 */
void JQ6500_MP3Player::pause() {
  _player->pause();
}

/**
 * Play next track.
 */
void JQ6500_MP3Player::nextTrack() {
  _player->next();
}

/**
 * Play next folder.
 */
void JQ6500_MP3Player::nextFolder() {
  _player->nextFolder();
}

/**
 * Play previous track.
 */
void JQ6500_MP3Player::previousTrack() {
  _player->prev();
}

/**
 * Play previous folder.
 */
void JQ6500_MP3Player::previousFolder() {
  _player->prevFolder();
}

/**
 * Play a specific file in a specific folder.
 */
void JQ6500_MP3Player::playSpecific(unsigned int folder, unsigned int track) {
  _player->playFileNumberInFolderNumber(folder, track);
}

/**
 * Reset the device (softly).
 */
void JQ6500_MP3Player::reset() {
  _player->reset();
}

/**
 * Get volume.
 */
int JQ6500_MP3Player::getVolume() {
  volume = _player->getVolume();
  return volume;
}

/**
 * Set volume.
 */
void JQ6500_MP3Player::setVolume(int newVolume) {
  volume = newVolume;
  _player->setVolume(volume);
}

/**
 * Increase the volume by 1.
 */
int JQ6500_MP3Player::volumeUp() {
  if (volume < _maxVolume) {
    volume += 1;

    _player->volumeUp();
  }

  return volume;
}

/**
 * Decrease the volume by 1.
 */
int JQ6500_MP3Player::volumeDown() {
  if (volume > _minVolume) {
    volume -= 1;

    _player->volumeDn();
  }

  return volume;
}

/**
 * Set the source to read data from.
 */
void JQ6500_MP3Player::setSource(int source) {
  _source = source;
  _player->setSource(_source);
}

/**
 * Get equalizer mode.
 */
int JQ6500_MP3Player::getEqualizer() {
  equalizerMode = _player->getEqualizer();

  return equalizerMode;
}

/**
 * Set equalizer mode.
 */
void JQ6500_MP3Player::setEqualizer(int mode) {
  equalizerMode = mode;

  _player->setEqualizer(equalizerMode);
}

/**
 * Cycle through available equalizer modes.
 */
void JQ6500_MP3Player::cycleEqualizer() {
  if (equalizerMode < TOTAL_EQ_MODES - 1) {
    equalizerMode += 1;
  } else {
    equalizerMode = 0;
  }

  setEqualizer(equalizerMode);
}

const char* JQ6500_MP3Player::getEqualizerModeName() {
  return equalizerModes[equalizerMode];
}

/**
 * Get loop mode.
 */
int JQ6500_MP3Player::getLoopMode() {
  loopMode = _player->getLoopMode();

  return loopMode;
}

const char* JQ6500_MP3Player::getLoopModeName() {
  return loopModes[loopMode];
}

/**
 * Set loop mode.
 */
void JQ6500_MP3Player::setLoopMode(int mode) {
  loopMode = mode;
  _player->setLoopMode(loopMode);
}

/**
 * Cycle through available loop modes.
 */
void JQ6500_MP3Player::cycleLoopMode() {
  if (loopMode < TOTAL_LOOP_MODES - 1) {
    loopMode += 1;
  } else {
    loopMode = 0;
  }

  setLoopMode(loopMode);
}

/**
 * Count the number of files on the specified media.
 */
unsigned int JQ6500_MP3Player::getTotalFiles(byte source) {
  return _player->countFiles(source);
}

/**
 * Count the number of folders on the specified media.
 */
unsigned int JQ6500_MP3Player::getTotalFolders(byte source) {
  return _player->countFolders(source);
}

/**
 * Get the name of the "current" file on the SD Card.
 */
void JQ6500_MP3Player::getCurrentFileName() {
  _player->currentFileName(currentFileName, sizeof(currentFileName));
}

/**
 * For the currently playing (or paused, or file that would be
 * played next if stopped)file, return the file's (FAT table)
 * index number.
 */
unsigned int JQ6500_MP3Player::currentFileIndex(byte source) {
  return _player->currentFileIndexNumber(source);
}

/**
 * Get total length in seconds of the currently playing or paused file.
 */
unsigned int JQ6500_MP3Player::currentFileLength() {
  return _player->currentFileLengthInSeconds();
}

/**
 * Get current position in seconds of the currently playing or paused file.
 */
unsigned int JQ6500_MP3Player::currentFilePosition() {
  return _player->currentFilePositionInSeconds();
}

/**
 * Get the status from the device.
 */
byte JQ6500_MP3Player::getStatus() {
  return _player->getStatus();
}
