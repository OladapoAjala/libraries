#include "inventoneBME280.h"
#include "Arduino.h"

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

uint8_t BME_SCK;
uint8_t BME_MISO;
uint8_t BME_MOSI;
uint8_t BME_CS;

//Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

unsigned long delayTime;

inventoneBME280::inventoneBME280 (uint8_t sck, uint8_t miso, uint8_t mosi, uint8_t cs){
    BME_SCK = sck;
    BME_MISO = miso;
    BME_MOSI = mosi;
    BME_CS = cs;

    Adafruit_BME280 _bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK);
    bme = _bme;
}

bool inventoneBME280::setupBME280() {
    bme.begin();
    delayTime = 1000;

    return true;
}

float inventoneBME280::getTemperature() {
    float temp;
    temp = bme.readTemperature();
    return temp;
}

float inventoneBME280::getPressure() {
    float pressure;
    pressure = bme.readPressure() / 100.0;
    return pressure;
}

float inventoneBME280::getAltitude() {
    float altitude;
    altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
    return altitude;
}

float inventoneBME280::getHumidity() {
    float humidity;
    humidity = bme.readHumidity();
    return humidity;
}