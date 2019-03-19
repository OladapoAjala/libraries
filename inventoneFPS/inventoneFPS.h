#ifndef inventoneFPS_h
#define inventoneDHT_h

#define ON true
#define OFF false

class inventoneFPS
{
    public:
        inventoneFPS(uint8_t rx_pin, uint8_t tx_pin);
        void setupFPS();
        //void turnLED(bool state);
        int searchFreeID();
        bool enrollFinger(int ID);
        //int findFingerID();
};

#endif