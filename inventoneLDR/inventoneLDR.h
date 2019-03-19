#ifndef inventoneLDR_h
#define inventoneLDR_h

#include "Arduino.h"

class inventoneLDR
{
    public:
        inventoneLDR(uint8_t pin);
        int getLightIntensity();
    private:
        int _pin;
};

#endif
