/*
  WaterFlowMeter.h - Control water flow meter.
*/
#ifndef WaterFlowMeter_h
#define WaterFlowMeter_h

#include "Arduino.h"
#include <FlowMeter.h>
#include <Preferences.h>

class WaterFlowMeter
{
  public:
    WaterFlowMeter() {};
    WaterFlowMeter(int pin, const char * ns);
    void begin();
    void reset();
    void saveHistoric();
    void measure(unsigned long period);
    double getTotalVolume();
    double getHistoricVolume();
    double getFlowRate();

  private:
    int _pin;
    Preferences* _prefs;
    const char * _namespace;
    const char* keyName = "water_volume";

    // see https://github.com/sekdiy/FlowMeter/issues/18#issuecomment-633074564
    const double cap = 10.0f;  // l/min
    const double kf = 11.0f;   // Hz per l/min
};

#endif