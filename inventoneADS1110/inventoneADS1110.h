#ifndef inventoneADS1110_h
#define inventoneADS1110_h

#include "Arduino.h"
#include "ADS1110.h"

class inventoneADS1110 : public ADS1110 
{
    public:
        inventoneADS1110 (byte address) : ADS1110 (address) {}
        byte    ping();
        byte    getGain();
        byte    getSampleRate();
        int     getVref();
        void    setGain(gain_t newGain);
        void    setSampleRate(sample_rate_t newRate);
        void    setVref(vref_t newVref);
        void    reset();
        int     getData();
        int     getVolt();  

};

#endif