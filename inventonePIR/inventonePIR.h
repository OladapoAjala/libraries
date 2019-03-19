#ifndef inventonePIR_h
#define inventonePIR_h

#include "Arduino.h"

class inventonePIR
{
    public:
        inventonePIR(int pirPin);
        bool isMotionDetected();
    private:
        int _pirPin;
};

#endif