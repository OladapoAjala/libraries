#include "inventoneMotor.h"

#include "Arduino.h"

inventoneMotor::inventoneMotor(uint8_t pin){
    pinMode (pin, OUTPUT);
    _pin = pin;
}

bool inventoneMotor::rotate(int speed){
    analogWrite (_pin, speed);
    return true;
}