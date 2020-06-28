/*
  SolarTracker.h - Track sun using 4 LDRs (light-dependent resistors).
*/
#ifndef SolarTracker_h
#define SolarTracker_h

#include <Arduino.h>
#include <GL55xx_LightSensor.h>

struct Tracker_Result {
    float array[4];
};

class SolarTracker
{
  public:
    SolarTracker(
      int ldr_east_pin,
      int ldr_west_pin,
      int ldr_north_pin,
      int ldr_south_pin
    );
    void begin();
    void loop();
    Tracker_Result read();

  private:
    GL55xx_LightSensor* _east;
    GL55xx_LightSensor* _west;
    GL55xx_LightSensor* _north;
    GL55xx_LightSensor* _south;
};

#endif