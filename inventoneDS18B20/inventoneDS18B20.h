#ifndef inventoneDS18B20_h
#define inventoneDS18B20_h

#include "Arduino.h"

class inventoneDS18B20
{
    public:
        inventoneDS18B20 (int pin);
        bool setupDS18B20 ();
        float getTemperatureIn(char tempUnit);
};

#endif
