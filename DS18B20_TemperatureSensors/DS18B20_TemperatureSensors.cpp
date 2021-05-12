/*
  DS18B20_TemperatureSensors.cpp - Control up to 8 DS18B20 temperature sensors using 1 GPIO connection.
*/

#include "DS18B20_TemperatureSensors.h"

/**
 * Constructor.
 *
 * @param oneWire_pin
 */
DS18B20_TemperatureSensors::DS18B20_TemperatureSensors(int oneWire_pin) {
  _oneWirePin = oneWire_pin;

  // initialize temperature sensor(s)
  _oneWire = new OneWire(_oneWirePin);
  _tempSensors = new DallasTemperature(_oneWire);
}

void DS18B20_TemperatureSensors::begin() {
  _tempSensors->begin();
}

void DS18B20_TemperatureSensors::loop() {
}

float DS18B20_TemperatureSensors::getTemperatureByIndex(int index) {
  _tempSensors->requestTemperatures();
  float temp = _tempSensors->getTempCByIndex(index);

  // invalid reading
  if (temp == -127 || temp > 100) {
    // something's wrong
    temp = 0;
  }

  return temp;
}

void DS18B20_TemperatureSensors::scan() {
  // update temp sensors count
  totalTempSensors = _tempSensors->getDeviceCount();

  // locate devices on the bus
  Serial.print(F("Locating temperature sensors... "));
  Serial.print(F("Found "));
  Serial.print(totalTempSensors, DEC);
  Serial.println(F(" sensors."));
  Serial.println();

  // loop through each device, print out address
  for (_deviceIndex=0; _deviceIndex<totalTempSensors; _deviceIndex++) {
    // Search the wire for address
    if (_tempSensors->getAddress(_tempDeviceAddress, _deviceIndex)) {
      Serial.print(F("Found device "));
      Serial.print(_deviceIndex, DEC);
      Serial.print(F(" with address: "));
      printAddress(_tempDeviceAddress);
      Serial.println();
    } else {
      Serial.print(F("Found ghost device at "));
      Serial.print(_deviceIndex, DEC);
      Serial.print(F(" but could not detect address. Check power and cabling"));
    }
  }
  Serial.println("---------------------------------------------");
  Serial.println();
}

void DS18B20_TemperatureSensors::printAddress(DeviceAddress deviceAddress) {
  // prints a temperature sensor address
  for (uint8_t i = 0; i < 8; i++) {
    if (deviceAddress[i] < 16) {
      Serial.print(F("0"));
      Serial.print(deviceAddress[i], HEX);
    }
  }
}
