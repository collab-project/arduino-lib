/*  Copyright (c) 2021, Collab
 *  All rights reserved
*/
/*
  KY006_Buzzer.h - Control KY-006 passive piezo buzzer.
*/
#ifndef KY006_Buzzer_h
#define KY006_Buzzer_h

#include <Arduino.h>

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
