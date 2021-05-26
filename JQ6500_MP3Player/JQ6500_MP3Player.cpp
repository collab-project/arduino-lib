/*  Copyright (c) 2020-2021, Collab
 *  All rights reserved
*/
/*
  JQ6500_MP3Player.cpp - Control JQ6500 MP3 player.
*/

#include <JQ6500_MP3Player.h>

JQ6500_MP3Player::JQ6500_MP3Player(
  short rx_pin,
  short tx_pin,
  int volume,
  int source,
  long baud_rate
) {
  _player = new JQ6500_Serial(rx_pin, tx_pin);
  _volume = volume;
  _source = source;
  _baudRate = baud_rate;
}

/**
 * Setup device.
 */
void JQ6500_MP3Player::begin() {
  _player->begin(_baudRate);
  reset();

  setSource(_source);
  setVolume(_volume);
  //getEqualizer();

  setLoopMode(MP3_LOOP_FOLDER);
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
  _volume = _player->getVolume();
  return _volume;
}

/**
 * Set volume.
 */
void JQ6500_MP3Player::setVolume(int volume) {
  _volume = volume;
  _player->setVolume(_volume);
}

/**
 * Increase the volume by 1.
 */
void JQ6500_MP3Player::volumeUp() {
  _player->volumeUp();
}

/**
 * Decrease the volume by 1.
 */
void JQ6500_MP3Player::volumeDown() {
  _player->volumeDn();
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
  _equalizerMode = _player->getEqualizer();
  return _equalizerMode;
}

/**
 * Set equalizer mode.
 */
void JQ6500_MP3Player::setEqualizer(int equalizerMode) {
  _equalizerMode = equalizerMode;
  _player->setEqualizer(_equalizerMode);
}

/**
 * Get loop mode.
 */
int JQ6500_MP3Player::getLoopMode() {
  _loopMode = _player->getLoopMode();
  return _loopMode;
}

/**
 * Set loop mode.
 */
void JQ6500_MP3Player::setLoopMode(int loopMode) {
  _loopMode = loopMode;
  _player->setLoopMode(_loopMode);
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
 * Get the status from the device.
 */
byte JQ6500_MP3Player::getStatus() {
  return _player->getStatus();
}

void JQ6500_MP3Player::loop() {
  /*
  // DONT PUT THIS IN LOOP, IT SLOWS FASTLED DOWN
  if (_player->getStatus() != MP3_STATUS_PLAYING) {
    _player->next();
  }*/
  /*
  char buffer[20];
  _player->currentFileName(buffer, sizeof(buffer));
  Serial.print("Now playing: ");
  Serial.println(buffer);
  */
}
