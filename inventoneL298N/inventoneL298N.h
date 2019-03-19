#ifndef inventoneL298N_h
#define inventoneL298N_h
#include "Arduino.h"

#define CLOCKWISE true
#define ANTICLOCKWISE false

class inventoneL298N
{
    public:
       inventoneL298N(uint8_t enPin, uint8_t IN1, uint8_t IN2); 
       bool setSpeed(uint16_t speed, bool direction);
    private:
        uint8_t _IN1;
        uint8_t _IN2;
};

#endif