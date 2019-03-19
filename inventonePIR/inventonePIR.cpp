#include "inventonePIR.h"
#include "Arduino.h"

inventonePIR::inventonePIR(int pirPin){
    pinMode (pirPin, INPUT);
    _pirPin = pirPin;
}

bool inventonePIR::isMotionDetected() {
    if (digitalRead(_pirPin) == HIGH){
        return true;
    }
    else return false;

    delay (2000);
}
