/*  Copyright (c) 2021-2022, Collab
 *  All rights reserved
*/
/*
  KY006_Buzzer.h - Control KY-006 piezo buzzer.
*/
#ifndef KY006_Buzzer_h
#define KY006_Buzzer_h

#include <Arduino.h>
#if defined(ESP32)
#include <Tone32.h>
#endif

class KY006_Buzzer
{
  public:
    KY006_Buzzer(
      int buzzer_pin
    );
    void begin();
    void enable(unsigned int frequency = 1000, unsigned long duration = 100);
    void disable();

  private:
    int _buzzerPin;
};

#endif
