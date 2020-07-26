/*
  ADS1115_Expander.cpp - Control ADS1115 analog ADC.
*/

#include "ADS1115_Expander.h"

ADS1115_Expander::ADS1115_Expander(float max_voltage, int i2c_addr, ADS1115_RANGE voltage_range) {
  _maxVoltage = max_voltage;
  _i2cAddress = i2c_addr;
  _voltageRange = voltage_range;

  _adc = new ADS1115_WE(_i2cAddress);
}

void ADS1115_Expander::begin() {
  if (!_adc->init()) {
    Serial.println("ADS1115 not connected!");
  }

  /* Set the voltage range of the ADC to adjust the gain
   * Please note that you must not apply more than VDD + 0.3V to the input pins!
   *
   * ADS1115_RANGE_6144  ->  +/- 6144 mV
   * ADS1115_RANGE_4096  ->  +/- 4096 mV
   * ADS1115_RANGE_2048  ->  +/- 2048 mV (default)
   * ADS1115_RANGE_1024  ->  +/- 1024 mV
   * ADS1115_RANGE_0512  ->  +/- 512 mV
   * ADS1115_RANGE_0256  ->  +/- 256 mV
  */
  _adc->setVoltageRange_mV(_voltageRange);
}

void ADS1115_Expander::loop() {
}

float ADS1115_Expander::readChannel(ADS1115_MUX channel) {
  _adc->setCompareChannels(channel);
  _adc->startSingleMeasurement();

  while (_adc->isBusy()) {}

  return _adc->getResult_mV();
}

ADS1115Result ADS1115_Expander::readAll() {
  ADS1115Result result;
  result.channel0 = readChannel(ADS1115_COMP_0_GND);
  result.channel1 = readChannel(ADS1115_COMP_1_GND);
  result.channel2 = readChannel(ADS1115_COMP_2_GND);
  result.channel3 = readChannel(ADS1115_COMP_3_GND);

  return result;
}
