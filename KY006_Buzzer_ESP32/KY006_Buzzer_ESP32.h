/*  Copyright (c) 2022-2023, Collab
 *  All rights reserved
*/
/*
  KY006_Buzzer_ESP32.h - Control KY-006 piezo buzzer for ESP32
*/
#ifndef KY006_Buzzer_ESP32_h
#define KY006_Buzzer_ESP32_h

#include <Arduino.h>

class KY006_Buzzer_ESP32
{
  public:
    KY006_Buzzer_ESP32(
      int buzzer_pin,
      int channel = 0
    );
    void begin();
    void enable(note_t frequency, unsigned long duration = 5);
    void disable();

  private:
    int _buzzerPin;
    int _channel;
};

#endif
