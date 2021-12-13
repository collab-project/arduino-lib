/*
* Copyright (c) 2021 Collab
* All rights reserved
*/
/*
   RemoteControl.h - Remote control.
*/

#ifndef RemoteControl_h
#define RemoteControl_h

#define RAW_BUFFER_LENGTH 100

#include <Arduino.h>
#include <Method.h>
#include <IRremoteInt.h>

class RemoteControl
{
  public:
    RemoteControl(
      int pin,
      Method cmd_recv_cb,
      bool led_feedback = ENABLE_LED_FEEDBACK,
      int led_pin = 0,
      bool debug = false
    );
    void begin();
    void loop();
    void printSummary();

  private:
    bool _debug;
    int _ledPin;
    int _receivePin;
    bool _ledFeedback;
    Method _cmdReceiveCallback;
};

#endif
