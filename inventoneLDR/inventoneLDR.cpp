#include "Arduino.h"
#include "inventoneLDR.h"

inventoneLDR::inventoneLDR(uint8_t pin){
    pinMode(pin, OUTPUT);
    _pin = pin;
}

int inventoneLDR::getLightIntensity(){
    int lightIntensity = analogRead(_pin);
    return lightIntensity;
}