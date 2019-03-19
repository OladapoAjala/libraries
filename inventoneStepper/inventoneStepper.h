#ifndef inventoneStepper_h
#define inventoneStepper_h

#include "Arduino.h"

class inventoneStepper
{
    public:
        inventoneStepper (uint8_t _pin1, uint8_t _pin2, uint8_t _pin3, uint8_t _pin4);
        void setupMotor(int maxSpeed, int speed, int accel, int position);
        void turnMotor ();
};

#endif