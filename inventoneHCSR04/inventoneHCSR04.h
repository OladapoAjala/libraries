#ifndef inventoneHCSR04_h
#define inventoneHCSR04_h

#include "Arduino.h"

class inventoneHCSR04
{
    public:
        inventoneHCSR04(int trigPin, int echoPin);
        float getDistanceIn(char distUnit[]);
};

#endif