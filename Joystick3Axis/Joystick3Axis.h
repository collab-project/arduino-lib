/*  Copyright (c) 2022, Collab
 *  All rights reserved
*/
/*
  Joystick3Axis.h - Control 3-axis joystick with button.
*/
#ifndef Joystick3Axis_h
#define Joystick3Axis_h

#include <Arduino.h>

class Joystick3Axis
{
  public:
    Joystick3Axis(
      int x_axis_pin,
      int y_axis_pin,
      int z_axis_pin,
      int button_pin
    );
    void begin();
    int readButton();
    int readXAxis(int deadzone = 0);
    int readYAxis(int deadzone = 0);
    int readZAxis(int deadzone = 0);

  private:
    int _xAxisPin;
    int _yAxisPin;
    int _zAxisPin;
    int _buttonPin;

    int applyDeadzone(int value, int deadzone, int min = -512, int max = 512);
};

#endif
