#ifndef inventoneADSWeather_h
#define inventoneADSWeather_h

#include "Arduino.h"

class inventoneADSWeather
{
    public:
        inventoneADSWeather(int rainPin, int windDirPin, int windSpdPin);
        void setupADSWeather();
        int detectRainAmount();
        int detectWindSpeed();
        int detectWindDirection();

};

#endif
