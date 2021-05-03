/*  Copyright (c) 2020-2021, Collab
 *  All rights reserved
*/
/*
  YX5300_AudioPlayer.cpp - Control YX5300 audio player.
*/

#include <YX5300_AudioPlayer.h>

YX5300_AudioPlayer::YX5300_AudioPlayer(
  short rx_pin,
  short tx_pin,
  uint8_t volume,
  uint32_t timeout
) {
  _volume = volume;
  _timeOut = timeout;

  _stream = new SoftwareSerial(rx_pin, tx_pin);
  _player = new MD_YX5300(*_stream);
}

void cbResponse(const MD_YX5300::cbData *status) {
  if (status->code != MD_YX5300::STS_ACK_OK) {
    Serial.print(F("MD_YX5300 - "));
  }

  switch (status->code) {
    case MD_YX5300::STS_OK:
      Serial.println(F("STS_OK"));
      break;

    case MD_YX5300::STS_TIMEOUT:
      Serial.println(F("STS_TIMEOUT"));
      break;

    case MD_YX5300::STS_VERSION:
      Serial.println(F("STS_VERSION"));
      break;

    case MD_YX5300::STS_CHECKSUM:
      Serial.println(F("STS_CHECKSUM"));
      break;

    case MD_YX5300::STS_TF_INSERT:
      // card has been inserted
      Serial.println(F("Card inserted."));
      break;

    case MD_YX5300::STS_TF_REMOVE:
      // card has been removed
      Serial.println(F("Card removed."));
      break;

    case MD_YX5300::STS_ACK_OK:
      //Serial.println(F("STS_ACK_OK"));
      break;

    case MD_YX5300::STS_FILE_END:
      Serial.println(F("File ended."));
      break;

    case MD_YX5300::STS_ERR_FILE:
      Serial.println(F("STS_ERR_FILE"));
      break;

    case MD_YX5300::STS_INIT:
      Serial.println(F("STS_INIT"));
      break;

    case MD_YX5300::STS_STATUS:
      Serial.println(F("STS_STATUS"));
      break;

    case MD_YX5300::STS_EQUALIZER:
      Serial.println(F("STS_EQUALIZER"));
      break;

    case MD_YX5300::STS_VOLUME:
      Serial.print(F("Volume:\t\t"));
      Serial.println(status->data);
      break;

    case MD_YX5300::STS_TOT_FILES:
      Serial.print(F("Total files:\t"));
      Serial.println(status->data);
      break;

    case MD_YX5300::STS_PLAYING:
      Serial.print(F("Playing file "));
      Serial.println(status->data);
      break;

    case MD_YX5300::STS_FLDR_FILES:
      Serial.println(F("STS_FLDR_FILES"));
      break;

    case MD_YX5300::STS_TOT_FLDR:
      Serial.print(F("Total folders:\t"));
      Serial.println(status->data);
      break;

    default:
      Serial.print(F("STS_??? 0x"));
      Serial.println(status->code, HEX);
      break;
  }

  //Serial.print(F(", 0x"));
  //Serial.println(status->data, HEX);
}

void YX5300_AudioPlayer::begin() {
  _stream->begin(MD_YX5300::SERIAL_BPS);
  _player->begin();
  _player->setSynchronous(false);
  _player->setCallback(cbResponse);
  setTimeout(_timeOut);
  setVolume(_volume);
}

void YX5300_AudioPlayer::loop() {
  _player->check();
}

void YX5300_AudioPlayer::query() {
  _player->queryFilesCount();
  _player->queryVolume();
}

void YX5300_AudioPlayer::stop() {
  Serial.println(F("MD_YX5300 - Stop playback"));

  _player->playStop();
}

void YX5300_AudioPlayer::playFolderRepeat(uint8_t folder) {
  _player->playFolderRepeat(folder);
}

void YX5300_AudioPlayer::playFolderShuffle(uint8_t folder) {
  _player->playFolderShuffle(folder);
}

/**
 * Play the next track.
*/
void YX5300_AudioPlayer::nextTrack() {
  Serial.println(F("MD_YX5300 - Play next track"));

  _player->playNext();
}

/**
 * Play the previous track.
*/
void YX5300_AudioPlayer::prevTrack() {
  Serial.println(F("MD_YX5300 - Play previous track"));

  _player->playPrev();
}

/**
 * @param index The file indexed (0-255) to be played.
*/
void YX5300_AudioPlayer::playTrack(uint8_t index) {
  _player->playTrack(index);
}

/**
 * Set the volume.
*/
void YX5300_AudioPlayer::setVolume(uint8_t volume) {
  _player->volume(volume);
}

/**
 * Return the maximum possible volume level.
*/
uint8_t YX5300_AudioPlayer::getMaxVolume() {
  return _player->volumeMax();
}

/**
 * Enable shuffle playing mode.
*/
void YX5300_AudioPlayer::enableShuffle() {
  _player->shuffle(true);
}

/**
 * Disable shuffle playing mode.
*/
void YX5300_AudioPlayer::disableShuffle() {
  _player->shuffle(false);
}

/**
 * Mute the sound output from the DAC.
*/
void YX5300_AudioPlayer::mute() {
  _player->volumeMute(true);
}

/**
 * Unmute the sound output from the DAC.
*/
void YX5300_AudioPlayer::unmute() {
  _player->volumeMute(false);
}

/**
 * Wakes up the MP3 player from sleep mode.
*/
void YX5300_AudioPlayer::wakeUp() {
  _player->wakeUp();
}

/**
 * Enables the MP3 player sleep mode.
*/
void YX5300_AudioPlayer::sleep() {
  _player->sleep();
}

/**
 * Set the device response timeout in milliseconds.
 *
 * If a message is not received within this time a timeout error
 * status will be generated.
*/
void YX5300_AudioPlayer::setTimeout(uint32_t timeout) {
  _player->setTimeout(timeout);
}
