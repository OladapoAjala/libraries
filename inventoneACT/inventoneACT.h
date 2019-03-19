#ifndef inventonneACT_h
#define inventonneACT_h

#include "Arduino.h"

class inventoneACT
{
    public:
        inventoneACT (uint8_t pin);
        inventoneACT ();
        void setupForRead (uint8_t pin);
        void setupForWrite (uint8_t pin);
        void turnLedOn ();
        void turnLedOff ();
        void turnRelayOn ();
        void turnRelayOff ();
        void rotate(int speed);
        void turn(int degrees);
        float multiplex(float data1, float data2, char *conditon);
        float pass(float input, bool shouldPass);
        bool threshold(float data1, float data2, char *condition);
        int map(long data, long in_min, long in_max, long out_min, long out_max); 
        char *string(char *text);
        String buildText(String text1, float x, String text2);
        int analog_read(uint8_t pin);
        void analog_write(uint8_t pin, int value);
        bool digital_read(uint8_t pin);
        void digital_write(uint8_t pin, int value);
    private:
        uint8_t _pin;
};

#endif
