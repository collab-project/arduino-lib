/*
   RotaryEncoderPushButtonESP32.h - ESP32 version of rotary encoder with internal push button.
*/

#ifndef RotaryEncoderPushButtonESP32_h
#define RotaryEncoderPushButtonESP32_h

#include <Arduino.h>
#include <Method.h>
#include <AceButton.h>
#include <ESP32Encoder.h>

using namespace ace_button;

class RotaryEncoderPushButtonESP32
{
  public:
    RotaryEncoderPushButtonESP32(
      int a_pin,
      int b_pin,
      int btn_pin,
      Method btnPress_callback,
      Method btnRelease_callback,
      Method encoder_callback
    );
    void begin();
    void loop();
    int64_t getPosition();

    int rotation;

    enum EventType {
      ROTARY_CW                 = 1 << 3,
      ROTARY_CCW                = 1 << 4,
    };

  private:
    AceButton* _button;
    ESP32Encoder* _encoder;
    int64_t _position = 0;
    int64_t _value = 0;
    int _pinA;
    int _pinB;
    int _btnPin;

    // callbacks
    Method _encoderCallback;
};

#endif