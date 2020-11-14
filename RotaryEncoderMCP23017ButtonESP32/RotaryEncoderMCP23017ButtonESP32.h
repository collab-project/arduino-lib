/*
   RotaryEncoderMCP23017ButtonESP32.h - ESP32 version of rotary encoder with
   internal push button controlled by MCP23017 multiplexer.
*/

#ifndef RotaryEncoderMCP23017ButtonESP32_h
#define RotaryEncoderMCP23017ButtonESP32_h

#include <Arduino.h>
#include <Method.h>
#include <ESP32Encoder.h>
#include <Button_MCP23017.h>
#include <MultiPlexer_MCP23017.h>

class RotaryEncoderMCP23017ButtonESP32
{
  public:
    RotaryEncoderMCP23017ButtonESP32(
      uint8_t index,
      int a_pin,
      int b_pin,
      int btn_pin,
      Method btn_callback,
      Method encoder_callback,
      MultiPlexer_MCP23017* mcp,
      MCP_PORT port
    );
    void begin();
    void loop();
    int64_t getPosition();

    int rotation;

    enum EventType {
      ROTARY_CW  = 1 << 3,
      ROTARY_CCW = 1 << 4,
    };

  private:
    Button_MCP23017* _button;
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