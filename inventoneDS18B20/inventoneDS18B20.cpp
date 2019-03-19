#include "inventoneDS18B20.h"
#include "Arduino.h"

#include <OneWire.h>
#include <DallasTemperature.h>

int ONE_WIRE_BUS;

inventoneDS18B20::inventoneDS18B20(int pin){
    ONE_WIRE_BUS = pin;
}

    OneWire oneWire (ONE_WIRE_BUS);
    DallasTemperature sensors(&oneWire);

//Setup the sensor
bool inventoneDS18B20::setupDS18B20 (){
    sensors.begin();
    return true;
}

//Function that gets executed in the loop
float inventoneDS18B20::getTemperatureIn (char tempUnit){
    sensors.requestTemperatures();
    float temperature;
    
    switch (tempUnit){
        case 'C':
        case 'c':
            temperature = sensors.getTempCByIndex(0);
            return temperature;
            break;
        case 'F':
        case 'f':
            temperature = sensors.getTempFByIndex(0);
            return temperature;
            break;
        case 'K':
        case 'k':
            temperature = 273.15 + sensors.getTempCByIndex(0);
            return temperature;
            break;
        default:
            return 0.0;
    }

    delay(1000);
}