/*
  DualAxisJoystick.h - Control dual-axis joystick.
*/
#ifndef DualAxisJoystick_h
#define DualAxisJoystick_h

#include <Arduino.h>
#include <Joystick.h>
#include <AxisJoystick.h>

class DualAxisJoystick
{
  public:
    DualAxisJoystick(int switch_pin, int vrx_pin, int vry_pin, int adc_min = 0, int adc_max = 4095);
    void begin();
    void loop();
    String moveTitle(const Joystick::Move move);

  private:
    Joystick* _joystick;
    const int _axesDeviation = 100;
};

#endif