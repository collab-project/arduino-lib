/*
  JQ6500_MP3Player.h - Control JQ6500 MP3 player.
*/
#ifndef JQ6500_MP3Player_h
#define JQ6500_MP3Player_h

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <JQ6500_Serial.h>

class JQ6500_MP3Player
{
  public:
    JQ6500_MP3Player(short rx_pin, short tx_pin, int volume = 10, long speed = 9600);
    void begin();
    void loop();

  private:
    JQ6500_Serial* _player;
    long _speed;
    int _volume;
};

#endif