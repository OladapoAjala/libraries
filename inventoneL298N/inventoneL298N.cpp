#include "inventoneL298N.h"

inventoneL298N::inventoneL298N (uint8_t enPin, uint8_t IN1, uint8_t IN2){
    pinMode (enPin, OUTPUT);
    pinMode (IN1, OUTPUT);
    pinMode (IN2, OUTPUT);

    digitalWrite(enPin, HIGH);
    _IN1 = IN1;
    _IN2 = IN2;
}

bool inventoneL298N::setSpeed(uint16_t speed, bool direction){
    
    if (direction == CLOCKWISE){
        analogWrite(_IN1, speed);
        digitalWrite(_IN2, LOW);
    }
    else if (direction == ANTICLOCKWISE){
        digitalWrite(_IN1, LOW);
        analogWrite(_IN2, speed);
    }
    else
        return false;
    
    return true;
}

