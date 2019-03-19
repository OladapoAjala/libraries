#ifndef inventoneMotor_h
#define inventoneMotor_h

#include "Arduino.h"

class inventoneMotor
{
    public:
        inventoneMotor(uint8_t pin);
        bool rotate(int speed);
    private:
        int _pin;
};

#endif