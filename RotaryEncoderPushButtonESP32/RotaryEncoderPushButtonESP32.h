/*
   RotaryEncoderPushButtonESP32.h - ESP32 version of rotary encoder with internal push button.
*/

#ifndef RotaryEncoderPushButtonESP32_h
#define RotaryEncoderPushButtonESP32_h

#include <Arduino.h>
#include <Method.h>
#include <RotaryEncoder.h>

class RotaryEncoderPushButtonESP32
{
  public:
    RotaryEncoderPushButtonESP32(
      int a_pin,
      int b_pin,
      int btn_pin,
      Method btn_callback,
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
    int16_t _position = 0;
    int16_t _value = 0;
    int _buttonState = 0;
    int _pinA;
    int _pinB;
    int _btnPin;

    // callbacks
    Method _btnCallback;
    Method _encoderCallback;
};

#endif