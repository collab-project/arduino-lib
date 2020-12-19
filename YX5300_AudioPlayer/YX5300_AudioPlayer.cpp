/*  Copyright (c) 2020, Collab
 *  All rights reserved
*/
/*
  YX5300_AudioPlayer.cpp - Control YX5300 audio player.
*/

#include <YX5300_AudioPlayer.h>

YX5300_AudioPlayer::YX5300_AudioPlayer(short rx_pin, short tx_pin, int volume) {
  _player = new MD_YX5300(rx_pin, tx_pin);
  _volume = volume;
}

void cbResponse(const MD_YX5300::cbData *status) {
  Serial.print(F("\nCallback status: "));

  switch (status->code)
  {
    case MD_YX5300::STS_OK:         Serial.print(F("STS_OK"));         break;
    case MD_YX5300::STS_TIMEOUT:    Serial.print(F("STS_TIMEOUT"));    break;
    case MD_YX5300::STS_VERSION:    Serial.print(F("STS_VERSION"));    break;
    case MD_YX5300::STS_CHECKSUM:   Serial.print(F("STS_CHECKSUM"));    break;
    case MD_YX5300::STS_TF_INSERT:
      Serial.print(F("STS_TF_INSERT"));
      break;

    case MD_YX5300::STS_TF_REMOVE:  Serial.print(F("STS_TF_REMOVE"));  break;
    case MD_YX5300::STS_ERR_FILE:   Serial.print(F("STS_ERR_FILE"));   break;
    case MD_YX5300::STS_ACK_OK:     Serial.print(F("STS_ACK_OK"));     break;
    case MD_YX5300::STS_FILE_END:   Serial.print(F("STS_FILE_END"));   break;
    case MD_YX5300::STS_INIT:       Serial.print(F("STS_INIT"));       break;
    case MD_YX5300::STS_STATUS:     Serial.print(F("STS_STATUS"));     break;
    case MD_YX5300::STS_EQUALIZER:  Serial.print(F("STS_EQUALIZER"));  break;
    case MD_YX5300::STS_VOLUME:
      Serial.print(F("Volume: "));
      Serial.println(status->data);
      break;

    case MD_YX5300::STS_TOT_FILES:
      Serial.print(F("SD-card files: "));
      Serial.println(status->data);
      break;

    case MD_YX5300::STS_PLAYING:    Serial.print(F("STS_PLAYING"));    break;
    case MD_YX5300::STS_FLDR_FILES: Serial.print(F("STS_FLDR_FILES")); break;
    case MD_YX5300::STS_TOT_FLDR:   Serial.print(F("STS_TOT_FLDR"));   break;
    default: Serial.print(F("STS_??? 0x")); Serial.print(status->code, HEX); break;
  }

  Serial.print(F(", 0x"));
  Serial.print(status->data, HEX);
}

void YX5300_AudioPlayer::begin() {
  _player->begin();
  _player->setCallback(cbResponse);
  _player->setSynchronous(false);
  _player->volume(_volume);

  _player->queryFilesCount();
  _player->queryVolume();
  //_player->queryStatus();
  Serial.print("Max volume: ");
  Serial.println(_player->volumeMax());

  _player->playFolderRepeat(PLAY_FOLDER);
}

void YX5300_AudioPlayer::loop() {
  _player->check();
}
