#include "inventoneHCSR04.h"
#include "Arduino.h"

#include "HCSR04.h"

int dumTrigPin;
int dumEchoPin;

HCSR04 sensor(dumTrigPin, dumEchoPin);

inventoneHCSR04::inventoneHCSR04(int trigPin, int echoPin){
    HCSR04 _sensor(trigPin, echoPin);
    sensor = _sensor;
}


float inventoneHCSR04::getDistanceIn(char distUnit[]){
    
    float distanceInCm = sensor.dist();

    if (!strcmp(distUnit, "cm") || !strcmp(distUnit, "CM")){
        return distanceInCm;
    }
    else if (!strcmp(distUnit, "m") || !strcmp(distUnit, "M")){
        float distanceInM = distanceInCm/100;
        return distanceInM;
    }
    
}