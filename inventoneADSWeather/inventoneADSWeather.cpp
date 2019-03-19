#include "inventoneADSWeather.h"
#include "ADSWeather.h"

#define CALC_INTERVAL 1000

int _rainPin;
int _windDirPin;
int _windSpdPin;

unsigned long next_calculation;
unsigned long timer;

int wind_direction;
int wind_speed;
int rain_amount;


ADSWeather ads(_rainPin, _windDirPin, _windSpdPin);

inventoneADSWeather::inventoneADSWeather(int rainPin, int windDirPin, int windSpdPin) {
    ADSWeather _ads(rainPin, windDirPin, windSpdPin);
    ads = _ads;
    _rainPin = rainPin;
    _windDirPin = windDirPin;
    _windSpdPin = windSpdPin;
}

void inventoneADSWeather::setupADSWeather() {
    attachInterrupt(digitalPinToInterrupt(_rainPin), ads.countRain, FALLING); //ads.countRain is the ISR for the rain gauge.
    attachInterrupt(digitalPinToInterrupt(_windSpdPin), ads.countAnemometer, FALLING); //ads.countAnemometer is the ISR for the anemometer.
    next_calculation = millis() + CALC_INTERVAL;
}

int inventoneADSWeather::detectRainAmount() {
    timer = millis();
    ads.update();

    if (timer > next_calculation) {
        next_calculation = timer + CALC_INTERVAL;
        rain_amount = ads.getRain();
    }

    return rain_amount;
}

int inventoneADSWeather::detectWindSpeed() {
    timer = millis();
    ads.update();

    if (timer > next_calculation) {
        next_calculation = timer + CALC_INTERVAL;
        wind_speed = ads.getWindSpeed();
    }

    return wind_speed;
}

int inventoneADSWeather::detectWindDirection() {
    timer = millis();
    ads.update();

    if (timer > next_calculation) {
        next_calculation = timer + CALC_INTERVAL;
        wind_direction = ads.getWindDirection();
    }

    return wind_direction;
}