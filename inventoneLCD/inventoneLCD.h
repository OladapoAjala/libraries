#ifndef inventoneLCD_h
#define inventoneLCD_h

#include "Arduino.h"

class inventoneLCD
{
    public:
        inventoneLCD(uint8_t lenght, uint8_t breadth, int i2c_address);
        void setupLCD();
        void printText(char *text);
        void scrollText(int speed, char direction);
};

#endif