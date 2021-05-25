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

void JQ6500_MP3Player::begin() {
  _player->begin(_baudRate);
  _player->reset();

  setSource(_source);
  setVolume(_volume);

  _player->setLoopMode(MP3_LOOP_ALL);

  unsigned int totalLocalFiles = getTotalFiles(MP3_SRC_BUILTIN);
  Serial.print("Local files:\t");
  Serial.println(totalLocalFiles);

  unsigned int totalSDFiles = getTotalFiles(MP3_SRC_SDCARD);
  Serial.print("SD-card files:\t");
  Serial.println(totalSDFiles);

  Serial.print("Volume:\t\t");
  Serial.println(getVolume());

  Serial.print("Loop mode:\t");
  Serial.println(_player->getLoopMode());

  if (getStatus() != MP3_STATUS_PLAYING) {
    _player->next();
  }
}

void JQ6500_MP3Player::playSpecific(unsigned int folder, unsigned int track) {
  _player->playFileNumberInFolderNumber(folder, track);
}

int JQ6500_MP3Player::getVolume() {
  _volume = _player->getVolume();
  return _volume;
}

void JQ6500_MP3Player::setVolume(int volume) {
  _volume = volume;
  _player->setVolume(_volume);
}

void JQ6500_MP3Player::setSource(int source) {
  _source = source;
  _player->setSource(_source);
}

int JQ6500_MP3Player::getEqualizer() {
  _equalizerMode = _player->getEqualizer();
  return _equalizerMode;
}

void JQ6500_MP3Player::setEqualizer(int equalizerMode) {
  _equalizerMode = equalizerMode;
  _player->setEqualizer(_equalizerMode);
}

unsigned int JQ6500_MP3Player::getTotalFiles(int source) {
  return _player->countFiles(source);
}

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
