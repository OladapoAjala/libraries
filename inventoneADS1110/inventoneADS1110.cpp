#include "inventoneADS1110.h"

byte inventoneADS1110::ping() {
    return ADS1110::ping();
}

byte inventoneADS1110::getGain() {
    return ADS1110::getGain();
}

byte inventoneADS1110::getSampleRate() {
    return ADS1110::getSampleRate();
}

int inventoneADS1110::getVref() {
    return ADS1110::getVref();
}

void inventoneADS1110::setGain(gain_t newGain) {
    ADS1110::setGain(newGain);
}

void inventoneADS1110::setSampleRate(sample_rate_t newRate) {
    ADS1110::setSampleRate(newRate);
}

void inventoneADS1110::setVref(vref_t newVref) {
    ADS1110::setVref(newVref);
}

void inventoneADS1110::reset() {
    ADS1110::reset();
}

int inventoneADS1110::getData() {
    return ADS1110::getData();
}

int inventoneADS1110::getVolt() {
    return ADS1110::getVolt();
}