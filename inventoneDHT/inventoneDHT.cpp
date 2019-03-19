#include "Arduino.h"
#include "inventoneDHT.h"

#include "DHT.h"

int _pin;
int _dhtType;

DHT sensor(_pin, _dhtType);

//Use 11 for DHT11 and 22 for DHT22
inventoneDHT::inventoneDHT(uint8_t pin, uint8_t dhtType){
    DHT _sensor(pin, dhtType);
    sensor = _sensor;
}

bool inventoneDHT::setupDHT(){
    sensor.begin();
    return true;
}

float inventoneDHT::getTemperatureIn(char tempUnit){
    float temperature;
    delay(2000);

    switch (tempUnit){
        case 'C':
        case 'c':
            temperature = sensor.readTemperature();
            return temperature;
            break;
        case 'F':
        case 'f':
            temperature = sensor.readTemperature(true);
            return temperature;
            break;
        case 'K':
        case 'k':
            temperature = 273.15 + sensor.readTemperature();
            return temperature;
            break;
        default:
            return 0.00;
    }
}

float inventoneDHT::getHumidity(){
    float humidity;
    delay(2000);

    humidity = sensor.readHumidity();
    return humidity;
}

float inventoneDHT::getHeatIndex(char heatIndexUnit){
    float heatIndex;
    delay(2000);
    float h = sensor.readHumidity();
    float t = sensor.readTemperature();
    float f = sensor.readTemperature(true);

    switch (heatIndexUnit){
        case 'C':
        case 'c':
            heatIndex = sensor.computeHeatIndex(t, h, false);
            return heatIndex;
            break;
        case 'F':
        case 'f':
            heatIndex = sensor.computeHeatIndex(f,h);
            return heatIndex;
            break;
        default:
            return 0.00;
    }
}
    