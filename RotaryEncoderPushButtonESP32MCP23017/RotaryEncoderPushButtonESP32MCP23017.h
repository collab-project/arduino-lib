/*
   RotaryEncoderPushButtonESP32MCP23017.h - ESP32 MCP23017 version of rotary encoder with internal push button.
*/

#ifndef RotaryEncoderPushButtonESP32MCP23017_h
#define RotaryEncoderPushButtonESP32MCP23017_h

#include <Arduino.h>
#include <Method.h>
#include <Adafruit_MCP23017.h>
#include <RotaryEncoderMCP23017.h>

class RotaryEncoderPushButtonESP32MCP23017
{
  public:
    RotaryEncoderPushButtonESP32MCP23017(
      int a_pin,
      int b_pin,
      int btn_pin,
      Adafruit_MCP23017* mcp,
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
    int _pinA;
    int _pinB;
    int _btnPin;
    Adafruit_MCP23017* _mcp;

    // callbacks
    Method _btnCallback;
    Method _encoderCallback;
};

#endif