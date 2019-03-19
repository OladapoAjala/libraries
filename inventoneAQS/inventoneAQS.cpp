#include "inventoneAQS.h"
#include"AirQuality.h"

#include"Arduino.h"

#define HIGH_POLLUTION 0
#define MEDIUM_POLLUTION 1
#define LOW_POLLUTION 2
#define ZERO_POLLUTION 3

AirQuality aqs;
int airQuality = -1;

/*Note this sensor is an analog sensor*/
// inventoneAQS::inventoneAQS() {

// }

void inventoneAQS::setupAQS(uint8_t analogPin) {
    aqs.init(analogPin);
}

int inventoneAQS::getAirQuality() {
    airQuality = aqs.slope();

    if ( airQuality >= 0 ) {

        if ( airQuality == HIGH_POLLUTION) {
            /*Maximum air pollution, please attend to the environment*/
            return airQuality;
        } else if ( airQuality == MEDIUM_POLLUTION) {
            /*Medium scale pollution, return result to the user*/
            return airQuality;
        } else if ( airQuality == LOW_POLLUTION) {
            /*Low pollution return result to the user*/
            return airQuality;
        } else if ( airQuality == ZERO_POLLUTION ) {
            /*No pollution has occured yet, return result to the user*/
            return airQuality;
        }
    }
}