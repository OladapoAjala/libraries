#ifndef inventoneDotMatrix_h
#define inventoneDotMatrix_h

#include "Arduino.h"

class inventoneDotMatrix
{
    public: 
        inventoneDotMatrix (uint8_t DIN, uint8_t CS, uint8_t CLK, int noInUse);
        void setupMAX7219(uint16_t intensity);
        void printChar( char c);
        void printScrolledString(char *string, int scroll_speed);
        void printScrolledChar(char c, int scroll_speed);

};

#endif