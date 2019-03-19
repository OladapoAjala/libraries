#ifndef inventoneAdagioPro_h
#define inventoneAdagioPro_h

#include "Arduino.h"
#include "AdagioPro.h"

class inventoneAdagioPro: public AdagioPro
{
    public:
        inventoneAdagioPro(int rx_pin, int tx_pin, bool plc_mode) : AdagioPro(rx_pin, tx_pin, plc_mode) {}
        void setupAdagioPro();
        void turnLampOn();
        void turnLampOff();
        void AutoSyncronize();
        void RGB(int red, int green, int blue);
        //~inventoneAdagioPro();
};

#endif