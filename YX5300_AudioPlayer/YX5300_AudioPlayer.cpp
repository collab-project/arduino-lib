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
    int volume
) {
  _volume = volume;

  // MP3 player serial stream for comms
  _stream = new SoftwareSerial(rx_pin, tx_pin);
  _player = new MD_YX5300(*_stream);
}

void cbResponse(const MD_YX5300::cbData *status) {
  switch (status->code) {
    case MD_YX5300::STS_OK:         Serial.print(F("STS_OK"));         break;
    case MD_YX5300::STS_TIMEOUT:    Serial.print(F("STS_TIMEOUT"));    break;
    case MD_YX5300::STS_VERSION:    Serial.print(F("STS_VERSION"));    break;
    case MD_YX5300::STS_CHECKSUM:   Serial.print(F("STS_CHECKSUM"));    break;
    case MD_YX5300::STS_TF_INSERT:
      // card has been inserted
      Serial.println(F("STS_TF_INSERT"));
      break;

    case MD_YX5300::STS_TF_REMOVE:
      // card has been removed
      Serial.println(F("STS_TF_REMOVE"));
      break;

    case MD_YX5300::STS_ACK_OK:
      // ignore
      //Serial.print(F("STS_ACK_OK"));
      break;

    case MD_YX5300::STS_FILE_END:
      Serial.println(F("File ended."));
      break;

    case MD_YX5300::STS_ERR_FILE:   Serial.print(F("STS_ERR_FILE"));   break;
    case MD_YX5300::STS_INIT:       Serial.print(F("STS_INIT"));       break;
    case MD_YX5300::STS_STATUS:     Serial.print(F("STS_STATUS"));     break;
    case MD_YX5300::STS_EQUALIZER:  Serial.print(F("STS_EQUALIZER"));  break;
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

    case MD_YX5300::STS_FLDR_FILES: Serial.print(F("STS_FLDR_FILES")); break;
    case MD_YX5300::STS_TOT_FLDR:   Serial.print(F("STS_TOT_FLDR"));   break;
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
  _player->volume(_volume);
}

void YX5300_AudioPlayer::loop() {
  _player->check();
}

void YX5300_AudioPlayer::query() {
  _player->queryFilesCount();
  _player->queryVolume();

  Serial.print(F("Max volume:\t"));
  Serial.println(_player->volumeMax());
}

void YX5300_AudioPlayer::stop() {
  _player->playStop();
}

void YX5300_AudioPlayer::playFolderRepeat(uint8_t folder) {
  _player->playFolderRepeat(folder);
}

void YX5300_AudioPlayer::nextTrack() {
  _player->playNext();
}

/**
 * @param index The file indexed (0-255) to be played.
*/
void YX5300_AudioPlayer::playTrack(uint8_t index) {
  _player->playTrack(index);
}
