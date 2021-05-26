/*
* Copyright (c) 2021 Collab
* All rights reserved
*/
/*
   RemoteControl.h - Remote control.
*/

#ifndef RemoteControl_h
#define RemoteControl_h

#include <Arduino.h>
#include <Method.h>
#include <IRremoteInt.h>

class RemoteControl
{
  public:
    RemoteControl(
      int pin,
      int led_pin,
      Method cmd_recv_cb,
      bool led_feedback = ENABLE_LED_FEEDBACK
    );
    void begin();
    void loop();

  private:
    int _receivePin;
    int _ledPin;
    bool _ledFeedback;
    Method _cmdReceiveCallback;
};

#endif
