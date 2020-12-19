/*  Copyright (c) 2020, Collab
 *  All rights reserved
*/
/*
   KY040_RotaryEncoderESP32.h - ESP32 version of KY-040 rotary encoder with push button.
*/

#ifndef KY040_RotaryEncoderESP32_h
#define KY040_RotaryEncoderESP32_h

#include <Arduino.h>
#include <Method.h>
#include <RotaryEncoder.h>

class KY040_RotaryEncoderESP32
{
  public:
    KY040_RotaryEncoderESP32(
      int a_pin,
      int b_pin,
      int btn_pin,
      Method btnPress_callback,
      Method encoder_callback
    );
    void begin();
    void loop();
    int rotation;

    enum EventType {
      BUTTON_CLICKED            = 1 << 0,
      BUTTON_DOUBLE_CLICKED     = 1 << 1,
      BUTTON_LONG_PRESSED       = 1 << 2,

      ROTARY_CW                 = 1 << 3,
      ROTARY_CCW                = 1 << 4,
    };

  private:
    int _pinA;
    int _pinB;
    int _btnPin;
    int _buttonState = 0;
    int16_t _position = 0;
    int16_t _value = 0;

    // callback
    Method _btnPressCallback;
    Method _encoderCallback;
};

#endif