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

#if defined(ESP32)
YX5300_AudioPlayer::YX5300_AudioPlayer(
  HardwareSerial * serial,
  Method ready_callback,
  uint8_t volume,
  uint32_t timeout
) {
  _hwSerial = true;
  _volume = volume;
  _timeOut = timeout;
  _readyCallback = ready_callback;

  _stream = serial;
  _player = new MD_YX5300(*_stream);

  // callbacks
  setupCallbacks();
}
#endif

#if defined(__AVR__) || defined(ESP8266)
YX5300_AudioPlayer::YX5300_AudioPlayer(
  SoftwareSerial * serial,
  Method ready_callback,
  uint8_t volume,
  uint32_t timeout
) {
  _hwSerial = false;
  _volume = volume;
  _timeOut = timeout;
  _readyCallback = ready_callback;

  _stream = serial;
  _player = new MD_YX5300(*_stream);

  // callbacks
  setupCallbacks();
}
#endif

void YX5300_AudioPlayer::setupCallbacks() {
  _playerCallback.attachCallback(
    makeFunctor((Functor0 *)0, *this, &YX5300_AudioPlayer::onPlayerCallback)
  );
  _fileEndedCallback.attachCallbackIntArg(
    makeFunctor((Functor1<int> *)0, *this, &YX5300_AudioPlayer::onFileEnded)
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
      _totalFilesFolderCallback.callbackIntArg(data);
      break;

    case MD_YX5300::STS_TOT_FLDR:
      _totalFoldersCallback.callbackIntArg(data);
      break;

    case MD_YX5300::STS_FILE_END:
      _fileEndedCallback.callbackIntArg(data);
      break;

    default:
      // notify listeners
      _playerCallback.callback();
      break;
  }
}

void YX5300_AudioPlayer::begin() {
  // start serial
  #if defined(__AVR__) || defined(ESP8266)
  static_cast<SoftwareSerial*>(_stream)->begin(MD_YX5300::SERIAL_BPS);
  #else
  static_cast<HardwareSerial*>(_stream)->begin(MD_YX5300::SERIAL_BPS);
  #endif

  // init device
  _player->begin();
  _player->setSynchronous(false);
  _player->setCallback(cbResponse);

  // setting volume here screws up serial
  //setVolume(_volume);

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
  Log.info(F("MD_YX5300 - Stop playback" CR));

  _player->playStop();
}

/**
 * Set or reset the repeat playing mode for the specified folder.
 *
 * @param folder The source folder (1-99).
*/
void YX5300_AudioPlayer::playFolderRepeat(uint8_t folder) {
  _fileEnded = 0;

  _player->playFolderRepeat(folder);
}

/**
 * Shuffle playback for the specified folder.
 *
 * MD_YX5300's shuffle method is broken so this is a custom implementation
 * see https://github.com/MajicDesigns/MD_YX5300/issues/2 for more
 *
 * @param folder The source folder (1-99).
*/
void YX5300_AudioPlayer::playFolderShuffle(uint8_t folder) {
  _shuffleEnabled = true;

  // pick random track
  currentTrack = getRandomTrack(folder);

  Log.info(F("MD_YX5300 - Playing random track %d from folder %d" CR),
    currentTrack.index, currentTrack.folder
  );
  Log.info(CR);

  // start playback
  playSpecific(currentTrack.folder, currentTrack.index);
}

/**
 * Shuffle playback across all folders.
*/
void YX5300_AudioPlayer::playShuffle() {
  _shuffleAll = true;

  playFolderShuffle();
}

/**
 * Play the next track.
*/
void YX5300_AudioPlayer::nextTrack() {
  _fileEnded = 0;

  _player->playNext();
}

/**
 * Play the previous track.
*/
void YX5300_AudioPlayer::prevTrack() {
  _fileEnded = 0;

  _player->playPrev();
}

/**
 * Restart playing the current audio file.
*/
void YX5300_AudioPlayer::playStart() {
  _fileEnded = 0;

  _player->playStart();
}

/**
 * Play a specific file in a folder.
 *
 * @param folder The source folder (1-99).
 * @param track The file indexed (0-255) to be played.
*/
void YX5300_AudioPlayer::playSpecific(uint8_t folder, uint8_t track) {
  _fileEnded = 0;

  _player->playSpecific(folder, track);
}

/**
 * Set the volume.
 *
 * @param volume The volume level (0-30).
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
 *
 * @param timeout The timeout in milliseconds.
*/
void YX5300_AudioPlayer::setTimeout(uint32_t timeout) {
  _player->setTimeout(timeout);
}

/**
 * Get a random track.
*/
Track YX5300_AudioPlayer::getRandomTrack(uint8_t folder) {
  if (_playList.empty()) {
    unsigned int i = 0;
    unsigned int totalTracks;

    if (!_shuffleAll) {
      // only shuffle selected folder
      totalTracks = _folders.at(folder - 1);
      // fill tracks
      for (i = 0; i < totalTracks; i++) {
        Track trk = addTrack(i + 1, folder);

        _playList.push_back(trk);
      }
    } else {
      // shuffle all folders
      int prevTotal = 0;
      for (unsigned int j = 0; j < _folders.size(); j++) {
        totalTracks = _folders.at(j);

        if (j > 0) {
            prevTotal += _folders.at(j - 1);
        }
        // fill tracks
        for (i = 0; i < totalTracks; i++) {
          Track trk = addTrack(i + 1 + prevTotal, j + 1);

          _playList.push_back(trk);
        }
      }
    }

    // randomize seed
    srand(random(10));

    // randomize list
    std::random_shuffle(_playList.begin(), _playList.end());
  }

  // pick first randomized track and remove it from the list
  Track tr = _playList.at(0);
  _playList.erase(_playList.begin());

  return tr;
}

/**
 * Add track.
*/
Track YX5300_AudioPlayer::addTrack(uint8_t index, uint8_t folder) {
  Track trk;
  trk.index = index;
  trk.folder = folder;
  return trk;
}

/**
 * Triggered when file total for particular folder is available.
 *
 * @param total Total files found in folder.
*/
void YX5300_AudioPlayer::onFilesFolder(int total) {
  // add new folder
  _folders.push_back(total);

  Log.info(F("MD_YX5300 - Folder %d: %d tracks" CR),
    _folders.size(),
    _folders.back()
  );

  if (_folders.size() < totalFolders) {
    queryFolderFiles(_folders.size() + 1);
  } else {
    // all folders are loaded
    Log.info(F("MD_YX5300 - Finished loading %d folders." CR),
      _folders.size()
    );

    // notify listeners
    _readyCallback.callback();
  }
}

/**
 * Triggered when total folders are reported.
 *
 * @param total Total folders found.
*/
void YX5300_AudioPlayer::onTotalFolders(int total) {
  totalFolders = total;

  Log.info(F("MD_YX5300 - Total folders: %d" CR), totalFolders);

  if (_folders.size() != totalFolders) {
    // query total files for all folders, starting with the first
    queryFolderFiles(1);
  }
}

/**
 * Triggered when file playback ended.
 *
 * @param index Index number of the file just completed.
*/
void YX5300_AudioPlayer::onFileEnded(int index) {
  Log.info(F("MD_YX5300 - File %d ended" CR), index);

  // workaround for https://github.com/MajicDesigns/MD_YX5300/issues/14
  if (_fileEnded == 0) {
    // first file end status
    _fileEnded = 1;
  } else if (_fileEnded == 1) {
    // second and last file end status
    _fileEnded = 2;
  }
  if (_fileEnded == 2) {
    if (_repeatEnabled) {
      if (_shuffleEnabled) {
        // go to next shuffled track
        playFolderShuffle();
      } else {
        nextTrack();
      }
    }
  }
}

/**
 * Called when player fires a callback.
*/
void YX5300_AudioPlayer::onPlayerCallback() {
  const MD_YX5300::cbData* status = _player->getStatus();

  switch (status->code) {
    case MD_YX5300::STS_OK:
      Log.info(F("MD_YX5300 - STS_OK" CR));
      break;

    case MD_YX5300::STS_TIMEOUT:
      Log.info(F("MD_YX5300 - STS_TIMEOUT" CR));
      break;

    case MD_YX5300::STS_VERSION:
      Log.info(F("MD_YX5300 - STS_VERSION: %d" CR), status->data);
      break;

    case MD_YX5300::STS_CHECKSUM:
      Log.info(F("MD_YX5300 - STS_CHECKSUM: %d" CR), status->data);
      break;

    case MD_YX5300::STS_TF_INSERT:
      // card has been inserted
      Log.info(F("MD_YX5300 - Card inserted." CR));
      break;

    case MD_YX5300::STS_TF_REMOVE:
      // card has been removed
      Log.info(F("MD_YX5300 - Card removed." CR));
      break;

    case MD_YX5300::STS_ACK_OK:
      //Log.info(F("MD_YX5300 - STS_ACK_OK" CR));
      break;

    case MD_YX5300::STS_ERR_FILE:
      Log.info(F("MD_YX5300 - STS_ERR_FILE" CR));
      break;

    case MD_YX5300::STS_INIT:
      Log.info(F("MD_YX5300 - STS_INIT" CR));
      break;

    case MD_YX5300::STS_STATUS:
      Log.info(F("MD_YX5300 - STS_STATUS" CR));
      break;

    case MD_YX5300::STS_PLAYING:
      Log.info(F("MD_YX5300 - Playing file %d" CR), status->data);
      break;

    case MD_YX5300::STS_EQUALIZER:
      Log.info(F("MD_YX5300 - STS_EQUALIZER" CR));
      break;

    case MD_YX5300::STS_TOT_FILES:
      Log.info(F("MD_YX5300 - Total files:\t%d" CR), status->data);
      break;

    case MD_YX5300::STS_VOLUME:
      Log.info(F("MD_YX5300 - Volume:\t\t%d" CR), status->data);
      break;

    default:
      Log.info(F("MD_YX5300 - STS_??? 0x"));
      Serial.println(status->code, HEX);
      break;
  }

  //Log.info(F(", 0x" CR), status->data);
}
