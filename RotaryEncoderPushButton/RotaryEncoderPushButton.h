/*
   RotaryEncoderPushButton.h - Rotary encoder with internal push button.
*/

#ifndef RotaryEncoderPushButton_h
#define RotaryEncoderPushButton_h

// None of the functions or ISRs will get compiled but their prototypes are declared
#define LIBCALL_ENABLEINTERRUPT

#include <stdint.h>
#include <Arduino.h>
#include <Method.h>
#include <TimerOne.h>
#include <ClickEncoder.h>
#include <EnableInterrupt.h>

class RotaryEncoderPushButton
{
  public:
    RotaryEncoderPushButton(
      int a_pin,
      int b_pin,
      int btn_pin,
      Method btnPress_callback,
      Method encoder_callback
    );
    void begin();
    void loop();
    int16_t getValue();
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
    int16_t _last, _value;

    // callback
    Method _btnPressCallback;
    Method _encoderCallback;
};

#endif