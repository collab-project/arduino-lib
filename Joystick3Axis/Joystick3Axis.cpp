/*  Copyright (c) 2022, Collab
 *  All rights reserved
*/
/*
  Joystick3Axis.h - Control 3-axis joystick with button.
*/

#include "Joystick3Axis.h"

Joystick3Axis::Joystick3Axis(
  int x_axis_pin,
  int y_axis_pin,
  int z_axis_pin,
  int button_pin
) {
  _xAxisPin = x_axis_pin;
  _yAxisPin = y_axis_pin;
  _zAxisPin = z_axis_pin;
  _buttonPin = button_pin;
}

void Joystick3Axis::begin() {
  // button
  pinMode(_buttonPin, INPUT_PULLUP);

  // axes
  pinMode(_xAxisPin, INPUT);
  pinMode(_yAxisPin, INPUT);
  pinMode(_zAxisPin, INPUT);
}

int Joystick3Axis::readButton() {
  return digitalRead(_buttonPin);
}

int Joystick3Axis::readXAxis(int deadzone) {
  int value = analogRead(_xAxisPin);

  return applyDeadzone(value, deadzone);
}

int Joystick3Axis::readYAxis(int deadzone) {
  int value = analogRead(_yAxisPin);

  return applyDeadzone(value, deadzone);
}

int Joystick3Axis::readZAxis(int deadzone) {
  int value = analogRead(_zAxisPin);

  return applyDeadzone(value, deadzone);
}

int Joystick3Axis::applyDeadzone(int value, int deadzone, int min, int max) {
  value = map(value, 0, 4095, min, max);

  if (value > deadzone) {
    value = value - deadzone;
  } else if (value < -deadzone) {
    value = value + deadzone;
  } else if (abs(value) < deadzone) {
    value = 0;
  } else {
    value = 0;
  }

  return map(value, min + deadzone, max - deadzone, min, max);
}
