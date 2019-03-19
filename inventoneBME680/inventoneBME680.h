#ifndef inventoneBME680_h
#define inventoneBME680_h

#include "Arduino.h"

class inventoneBME680
{
    public:
        inventoneBME680 (uint8_t sck, uint8_t miso, uint8_t mosi, uint8_t cs);
        bool setupBME680();
        float getTemperature();
        float getPressure();
        float getAltitude();
        float getHumidity();
};

#endif