/*
  MultiPlexer_ADS1115.cpp - Control ADS1115 analog ADC.
*/

#include "MultiPlexer_ADS1115.h"

MultiPlexer_ADS1115::MultiPlexer_ADS1115(
  int i2c_addr,
  ADS1115_RANGE voltage_range
) {
  _i2cAddress = i2c_addr;
  _voltageRange = voltage_range;

  _adc = new ADS1115_WE(_i2cAddress);
}

void MultiPlexer_ADS1115::begin() {
  if (!_adc->init()) {
    Log.info(F("ADS1115 not connected!" CR));
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

int16_t MultiPlexer_ADS1115::readChannel(
  ADS1115_MUX channel, int16_t max_voltage, int16_t range_min, int16_t range_max
) {
  _adc->setCompareChannels(channel);
  _adc->startSingleMeasurement();

  while (_adc->isBusy()) {}

  return _adc->getResultWithRange(range_min, range_max, max_voltage);
}

int16_t MultiPlexer_ADS1115::readChannel0(int16_t max_voltage, int16_t range_min, int16_t range_max) {
  return readChannel(ADS1115_COMP_0_GND, max_voltage, range_min, range_max);
}

int16_t MultiPlexer_ADS1115::readChannel1(int16_t max_voltage, int16_t range_min, int16_t range_max) {
  return readChannel(ADS1115_COMP_1_GND, max_voltage, range_min, range_max);
}

int16_t MultiPlexer_ADS1115::readChannel2(int16_t max_voltage, int16_t range_min, int16_t range_max) {
  return readChannel(ADS1115_COMP_2_GND, max_voltage, range_min, range_max);
}

int16_t MultiPlexer_ADS1115::readChannel3(int16_t max_voltage, int16_t range_min, int16_t range_max) {
  return readChannel(ADS1115_COMP_3_GND, max_voltage, range_min, range_max);
}

ADS1115Result MultiPlexer_ADS1115::readAll(int16_t max_voltage, int16_t range_min, int16_t range_max) {
  ADS1115Result result;
  result.channel0 = readChannel0(max_voltage, range_min, range_max);
  result.channel1 = readChannel1(max_voltage, range_min, range_max);
  result.channel2 = readChannel2(max_voltage, range_min, range_max);
  result.channel3 = readChannel3(max_voltage, range_min, range_max);

  return result;
}
