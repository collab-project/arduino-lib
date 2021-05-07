/*  Copyright (c) 2020-2021, Collab
 *  All rights reserved
*/
/*
  YX5300_AudioPlayer.cpp - Control YX5300 audio player.
*/

#include <YX5300_AudioPlayer.h>

Method _playerCallback;
Method _fileEndedCallback;
Method _totalFoldersCallback;
Method _totalFilesFolderCallback;

YX5300_AudioPlayer::YX5300_AudioPlayer(
  short rx_pin,
  short tx_pin,
  Method ready_callback,
  uint8_t volume,
  uint32_t timeout
) {
  _volume = volume;
  _timeOut = timeout;
  _readyCallback = ready_callback;

  _stream = new SoftwareSerial(rx_pin, tx_pin);
  _player = new MD_YX5300(*_stream);

  // callbacks
  _playerCallback.attachCallback(
    makeFunctor((Functor0 *)0, *this, &YX5300_AudioPlayer::onPlayerCallback)
  );
  _fileEndedCallback.attachCallback(
    makeFunctor((Functor0 *)0, *this, &YX5300_AudioPlayer::onFileEnded)
  );
  _totalFoldersCallback.attachCallbackIntArg(
    makeFunctor((Functor1<int> *)0, *this, &YX5300_AudioPlayer::onTotalFolders)
  );
  _totalFilesFolderCallback.attachCallbackIntArg(
    makeFunctor((Functor1<int> *)0, *this, &YX5300_AudioPlayer::onFilesFolder)
  );
}

/**
 * Handler for callback provided by library.
*/
void cbResponse(const MD_YX5300::cbData *status) {
  uint16_t data = status->data;

  switch (status->code) {
    case MD_YX5300::STS_FLDR_FILES:
      // notify listeners
      _totalFilesFolderCallback.callbackIntArg(data);
      break;

    case MD_YX5300::STS_TOT_FLDR:
      // notify listeners
      _totalFoldersCallback.callbackIntArg(data);
      break;

    case MD_YX5300::STS_FILE_END:
      Serial.println(F("MD_YX5300 - File ended."));

      // notify listeners
      _fileEndedCallback.callback();
      break;

    case MD_YX5300::STS_VOLUME:
      Serial.print(F("MD_YX5300 - Volume:\t\t"));
      Serial.println(data);
      break;

    default:
      // notify listeners
      _playerCallback.callback();
      break;
  }
}

void YX5300_AudioPlayer::begin() {
  _stream->begin(MD_YX5300::SERIAL_BPS);
  _player->begin();
  _player->setSynchronous(false);
  _player->setCallback(cbResponse);
  setVolume(_volume);

  // get total folders once
  queryFolderCount();
}

void YX5300_AudioPlayer::loop() {
  _player->check();
}

/**
 * Query the number of folders on the device.
*/
void YX5300_AudioPlayer::queryFolderCount() {
  _player->queryFolderCount();
}

/**
 * Query the number of files in the specified folder.
*/
void YX5300_AudioPlayer::queryFolderFiles(uint8_t folder) {
  _player->queryFolderFiles(folder);
}

/**
 * Query the file currently playing.
*/
void YX5300_AudioPlayer::queryFile() {
  _player->queryFile();
}

/**
 * Request the current status setting from the device.
*/
void YX5300_AudioPlayer::queryStatus() {
  _player->queryStatus();
}

/**
 * Stop playing the current audio file.
*/
void YX5300_AudioPlayer::stop() {
  Serial.println(F("MD_YX5300 - Stop playback"));

  _player->playStop();
}

/**
 * Set or reset the repeat playing mode for the specified folder.
*/
void YX5300_AudioPlayer::playFolderRepeat(uint8_t folder) {
  _player->playFolderRepeat(folder);
}

/**
 * Shuffle playback for the specified folder.
 *
 * MD_YX5300's shuffle method is broken so this is a custom implementation
 * see https://github.com/MajicDesigns/MD_YX5300/issues/2 for more
*/
void YX5300_AudioPlayer::playFolderShuffle(uint8_t folder) {
  _shuffleEnabled = true;
  _fileEnded = false;

  // pick random track from folder
  state.currentFolderIndex = folder;
  state.currentTrackIndex = getRandomTrack(_folders.at(folder - 1));

  Serial.print(F("MD_YX5300 - Playing random track "));
  Serial.print(state.currentTrackIndex);
  Serial.print(F(" from folder "));
  Serial.println(state.currentFolderIndex);

  // start playback
  playSpecific(state.currentFolderIndex, state.currentTrackIndex);
}

/**
 * Play the next track.
*/
void YX5300_AudioPlayer::nextTrack() {
  _player->playNext();
}

/**
 * Play the previous track.
*/
void YX5300_AudioPlayer::prevTrack() {
  _player->playPrev();
}

/**
 * Restart playing the current audio file.
*/
void YX5300_AudioPlayer::playStart() {
  _player->playStart();
}

/**
 * @param folder The source folder (1-99).
 * @param track The file indexed (0-255) to be played.
*/
void YX5300_AudioPlayer::playSpecific(uint8_t folder, uint8_t track) {
  _player->playSpecific(folder, track);
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

/**
 * Get a random track.
*/
int YX5300_AudioPlayer::getRandomTrack(int totalTracks) {
  if (_playList.isEmpty()) {
    // fill array
    for (int i = 0; i < totalTracks; i++) {
      _playList.add(i);
    }
  }

  int rv = random(totalTracks);
  if (_playList.has(rv) == false) {
    for (int i = rv; i < rv + totalTracks; i++) {
      int idx = i % totalTracks;
      if (_playList.has(idx)) {
        rv = idx;
        break;
      }
    }
  }
  _playList.sub(rv);

  return rv + 1;
}

/**
 * Triggered when file total for particular folder is available.
*/
void YX5300_AudioPlayer::onFilesFolder(int total) {
  // add new folder
  _folders.push_back(total);

  Serial.print(F("MD_YX5300 - Folder "));
  Serial.print(_folders.size());
  Serial.print(F(": "));
  Serial.print(_folders.back());
  Serial.println(F(" tracks"));

  if (_folders.size() < state.totalFolders) {
    // this delay seems to be needed or audio player will stall after
    // querying 1st folder for total files
    delay(20);
    queryFolderFiles(_folders.size() + 1);
  } else {
    // all folders are loaded
    Serial.print(F("MD_YX5300 - Loaded "));
    Serial.print(_folders.size());
    Serial.println(F(" folders."));
    delay(20);

    // notify listeners
    _readyCallback.callback();
  }
}

/**
 * Triggered when total folders are reported.
*/
void YX5300_AudioPlayer::onTotalFolders(int total) {
  state.totalFolders = total;
  Serial.print(F("MD_YX5300 - Total folders: "));
  Serial.println(state.totalFolders);

  if (_folders.size() != state.totalFolders) {
    // query total files for all folders, starting with the first
    state.currentFolderIndex = 1;
    queryFolderFiles(state.currentFolderIndex);
  }
}

/**
 * Triggered when file playback ended.
*/
void YX5300_AudioPlayer::onFileEnded() {
  if (!_fileEnded) {
    _fileEnded = true;

    if (_shuffleEnabled) {
      // start shuffled playback
      //playFolderShuffle();
    }
  }
}

/**
 * Called when player fires a callback.
*/
void YX5300_AudioPlayer::onPlayerCallback() {
  const MD_YX5300::cbData* status = _player->getStatus();

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
      Serial.print(F("STS_VERSION: "));
      Serial.println(status->data);
      break;

    case MD_YX5300::STS_CHECKSUM:
      Serial.print(F("STS_CHECKSUM: "));
      Serial.println(status->data);
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

    case MD_YX5300::STS_ERR_FILE:
      Serial.println(F("STS_ERR_FILE"));
      break;

    case MD_YX5300::STS_INIT:
      Serial.println(F("STS_INIT"));
      break;

    case MD_YX5300::STS_STATUS:
      Serial.println(F("STS_STATUS"));
      break;

    case MD_YX5300::STS_PLAYING:
      Serial.print(F("Playing file "));
      Serial.println(status->data);
      break;

    case MD_YX5300::STS_EQUALIZER:
      Serial.println(F("STS_EQUALIZER"));
      break;

    case MD_YX5300::STS_TOT_FILES:
      Serial.print(F("Total files:\t"));
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
