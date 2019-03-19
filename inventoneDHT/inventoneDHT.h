#ifndef inventoneDHT_h
#define inventoneDHT_h

class inventoneDHT
{
    public:
        inventoneDHT(uint8_t pin, uint8_t dhtType);
        bool setupDHT();
        float getTemperatureIn(char tempUnit);
        float getHumidity();
        float getHeatIndex(char heatIndexUnit);
};

#endif