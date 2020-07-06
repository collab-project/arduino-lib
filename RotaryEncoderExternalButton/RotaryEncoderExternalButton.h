/*
   RotaryEncoderExternalButton.h - Rotary encoder with external push button.
*/

#ifndef RotaryEncoderExternalButton_h
#define RotaryEncoderExternalButton_h

// None of the functions or ISRs will get compiled but their prototypes are declared
#define LIBCALL_ENABLEINTERRUPT

#include <stdint.h>
#include <Arduino.h>
#include <Button.h>
#include <Method.h>
#include <TimerOne.h>
#include <ClickEncoder.h>
#include <EnableInterrupt.h>

class RotaryEncoderExternalButton
{
  public:
    RotaryEncoderExternalButton(
      int a_pin,
      int b_pin,
      int btn_pin,
      int stepsPerNotch,
      Method btn_callback,
      Method encoder_callback
    );
    void begin();
    void loop();
    int16_t getValue();

  private:
    int16_t _last, _value;
    int _buttonState = 0;
    int _pinA;
    int _pinB;
    int _btnPin;
    int _stepsPerNotch;
    Button* _btn;

    // callbacks
    Method _btnCallback;
    Method _encoderCallback;
};

#endif