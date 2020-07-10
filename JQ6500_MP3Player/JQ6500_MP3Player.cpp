/*
  JQ6500_MP3Player.cpp - Control JQ6500 MP3 player.
*/

#include <JQ6500_MP3Player.h>

JQ6500_MP3Player::JQ6500_MP3Player(short rx_pin, short tx_pin, int volume, long speed) {
  _player = new JQ6500_Serial(rx_pin, tx_pin);
  _speed = speed;
  _volume = volume;
}

void JQ6500_MP3Player::begin() {
  _player->begin(_speed);
  _player->reset();
  _player->setSource(MP3_SRC_SDCARD);
  _player->setVolume(_volume);
  _player->setLoopMode(MP3_LOOP_ALL);

  unsigned int totalLocalFiles = _player->countFiles(MP3_SRC_BUILTIN);
  Serial.print("Local files: ");
  Serial.println(totalLocalFiles);

  unsigned int totalSDFiles = _player->countFiles(MP3_SRC_SDCARD);
  Serial.print("SD-card files: ");
  Serial.println(totalSDFiles);

  Serial.print("Volume: ");
  Serial.println(_player->getVolume());

  Serial.print("Loop mode: ");
  Serial.println(_player->getLoopMode());

  if (_player->getStatus() != MP3_STATUS_PLAYING) {
    _player->next();
  }
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
