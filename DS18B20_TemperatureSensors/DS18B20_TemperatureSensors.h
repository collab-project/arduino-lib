/*
  DS18B20_TemperatureSensors.h - Control up to 8 DS18B20 temperature sensors using 1 GPIO connection.
*/
#ifndef DS18B20_TemperatureSensors_h
#define DS18B20_TemperatureSensors_h

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

class DS18B20_TemperatureSensors
{
  public:
    DS18B20_TemperatureSensors() {};
    DS18B20_TemperatureSensors(
      int oneWire_pin
    );
    int totalTempSensors;
    void begin();
    void loop();
    void scan();
    void printAddress(DeviceAddress deviceAddress);
    float getTemperatureByIndex(int index);

  private:
    OneWire* _oneWire;
    DallasTemperature* _tempSensors;
    DeviceAddress _tempDeviceAddress;
    int _oneWirePin;
    int _deviceIndex;
};

#endif