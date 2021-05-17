/*  Copyright (c) 2020-2021, Collab
 *  All rights reserved
*/
/*
  WaterFlowMeter.cpp - Control water flow meter.
*/

#include <WaterFlowMeter.h>

FlowMeter* _sensor;

// define an 'interrupt service handler' (ISR)
void countPulse() {
  // let our flow meter count the pulses
  _sensor->count();
}

WaterFlowMeter::WaterFlowMeter(int pin, const char * ns) {
  _pin = pin;
  _namespace = ns;

  // preferences storage
  _prefs = new Preferences();

  // flow sensor
  FlowSensorProperties sensorConfig = {cap, kf, {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.08955223881f, 0.08860759494f, 0.08791208791f, 0.08737864078f, 0.08771929825f}};
  _sensor = new FlowMeter(_pin, sensorConfig);
}

void WaterFlowMeter::begin() {
  // enable a call to the 'interrupt service handler' (ISR) on every
  // rising edge at the interrupt pin. do this setup step for every
  // ISR you have defined, depending on how many interrupts you use
  attachInterrupt(_pin, countPulse, RISING);

  // sometimes initializing the gear generates some pulses that we
  // should ignore
  _sensor->reset();
}

void WaterFlowMeter::measure(unsigned long period) {
  // process the (possibly) counted ticks
  _sensor->tick(period);
}

double WaterFlowMeter::getTotalVolume() {
  return _sensor->getTotalVolume();
}

double WaterFlowMeter::getFlowRate() {
  return _sensor->getCurrentFlowrate();
}

double WaterFlowMeter::getHistoricVolume() {
  _prefs->begin(_namespace, true);

  double historicLiters = _prefs->getDouble(keyName, 0);

  _prefs->end();

  return historicLiters;
}

void WaterFlowMeter::saveHistoric() {
  double liters = getTotalVolume();
  if (liters > 0) {
    _prefs->begin(_namespace, false);

    double historicLiters = _prefs->getDouble(keyName, 0);
    double updatedLiters = historicLiters + liters;

    // update data
    _prefs->putDouble(keyName, updatedLiters);

    _prefs->end();
  }
}

void WaterFlowMeter::reset() {
  _prefs->begin(_namespace, false);

  // reset to zero
  _prefs->putDouble(keyName, 0);

  _prefs->end();
}
