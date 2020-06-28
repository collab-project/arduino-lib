/*
  DualAxisJoystick.cpp - Control dual-axis joystick.
*/

#include "DualAxisJoystick.h"

/**
 * Constructor.
 */
DualAxisJoystick::DualAxisJoystick(int switch_pin, int vrx_pin, int vry_pin, int adc_min, int adc_max) {
  _joystick = new AxisJoystick(switch_pin, vrx_pin, vry_pin);
  _joystick->calibrate(adc_min, adc_max, _axesDeviation);
}

void DualAxisJoystick::begin() {
}


void DualAxisJoystick::loop() {
}

String DualAxisJoystick::moveTitle(const Joystick::Move move) {
  switch (move) {
    case Joystick::Move::NOT:
      return "CENTER";
    case Joystick::Move::PRESS:
      return "PRESS";
    case Joystick::Move::UP:
      return "RIGHT";
    case Joystick::Move::DOWN:
      return "LEFT";
    case Joystick::Move::RIGHT:
      return "UP";
    case Joystick::Move::LEFT:
      return "DOWN";
    default:
      return "???";
  }
}