/*
  MultiPlexer_ADS1115.cpp - Control ADS1115 analog ADC.
*/

#include "MultiPlexer_ADS1115.h"

MultiPlexer_ADS1115::MultiPlexer_ADS1115(
  float max_voltage,
  int i2c_addr,
  ADS1115_RANGE voltage_range
) {
  _maxVoltage = max_voltage;
  _i2cAddress = i2c_addr;
  _voltageRange = voltage_range;

  _adc = new ADS1115_WE(_i2cAddress);
}

void MultiPlexer_ADS1115::begin() {
  if (!_adc->init()) {
    Serial.println("ADS1115 not connected!");
  }

  /* Set the voltage range of the ADC to adjust the gain
   * Please note that you must not apply more than VDD + 0.3V to the input pins!
   *
   * ADS1115_RANGE_6144  ->  +/- 6144 mV
   * ADS1115_RANGE_4096  ->  +/- 4096 mV
   * ADS1115_RANGE_2048  ->  +/- 2048 mV
   * ADS1115_RANGE_1024  ->  +/- 1024 mV
   * ADS1115_RANGE_0512  ->  +/- 512 mV
   * ADS1115_RANGE_0256  ->  +/- 256 mV
  */
  _adc->setVoltageRange_mV(_voltageRange);
}

void MultiPlexer_ADS1115::loop() {
}

float MultiPlexer_ADS1115::readChannel(ADS1115_MUX channel) {
  _adc->setCompareChannels(channel);
  _adc->startSingleMeasurement();

  while (_adc->isBusy()) {}

  return _adc->getResult_mV();
}

float MultiPlexer_ADS1115::readChannel0() {
  return readChannel(ADS1115_COMP_0_GND);
}

float MultiPlexer_ADS1115::readChannel1() {
  return readChannel(ADS1115_COMP_1_GND);
}

float MultiPlexer_ADS1115::readChannel2() {
  return readChannel(ADS1115_COMP_2_GND);
}

float MultiPlexer_ADS1115::readChannel3() {
  return readChannel(ADS1115_COMP_3_GND);
}

ADS1115Result MultiPlexer_ADS1115::readAll() {
  ADS1115Result result;
  result.channel0 = readChannel0();
  result.channel1 = readChannel1();
  result.channel2 = readChannel2();
  result.channel3 = readChannel3();

  return result;
}
