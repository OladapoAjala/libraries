#ifndef inventoneAQS_h
#define inventoneAQS_h

#include "Arduino.h"

class inventoneAQS
{
    public:
        //inventoneAQS();
        void setupAQS(uint8_t analogPin);   
        int getAirQuality();
};

#endif