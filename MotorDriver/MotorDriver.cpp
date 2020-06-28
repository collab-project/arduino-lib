/*
  MotorDriver.cpp - Control H bridge module.
*/

#include <MotorDriver.h>

MotorDriver::MotorDriver(int enable_pin, int pwma_pin, int pwmb_pin) {
  _enablePin = enable_pin;
  _pwmaPin = pwma_pin;
  _pwmbPin = pwmb_pin;
}

void MotorDriver::begin() {

}

void MotorDriver::loop() {

}

void MotorDriver::enable() {

}

void MotorDriver::disable() {

}
