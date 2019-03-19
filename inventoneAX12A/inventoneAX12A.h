#ifndef inventoneAX12A_h
#define inventoneAX12A_h

#include "Arduino.h"
#include "AX12A.h"

#define TX_PIN (1)
#define DEFAULT_BAUD (1000000)

class inventoneAX12A
{
    public:
        inventoneAX12A ();
        void setupAX12A (long baudrate, unsigned char comPin, HardwareSerial *serialType);
        bool led (unsigned char ID, bool state);
        bool setupID (unsigned char ID, unsigned char newID);
        bool setupBD (unsigned char ID, long baud);
        int rotate(unsigned char ID, bool direction, int speed);
        int moveTo (unsigned char ID, int position);
        int moveTo (unsigned char ID, int position, int speed);
        int getTemperature (unsigned char ID);
        int getVoltage (unsigned char ID);
        int getPosition (unsigned char ID);
        int getSpeed (unsigned char ID);
        int getLoad (unsigned char ID);
        int setMaximumTorque (unsigned char ID, int maxTorque);
};

#endif