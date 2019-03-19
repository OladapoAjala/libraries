#ifndef inventoneBME280_h
#define inventoneBME280_h

#include "Arduino.h"

class inventoneBME280
{
    public:
        inventoneBME280 (uint8_t sck, uint8_t miso, uint8_t mosi, uint8_t cs);
        bool setupBME280();
        float getTemperature();
        float getPressure();
        float getAltitude();
        float getHumidity();
};

#endif