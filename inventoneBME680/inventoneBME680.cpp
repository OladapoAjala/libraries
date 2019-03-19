#include "inventoneBME680.h"
#include "Arduino.h"

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>

#define SEALEVELPRESSURE_HPA (1013.25)

uint8_t BME_SCK;
uint8_t BME_MISO;
uint8_t BME_MOSI;
uint8_t BME_CS;

//Adafruit_BME680 bme; // I2C
//Adafruit_BME680 bme(BME_CS); // hardware SPI
Adafruit_BME680 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

unsigned long delayTime;

inventoneBME680::inventoneBME680 (uint8_t sck, uint8_t miso, uint8_t mosi, uint8_t cs){
    BME_SCK = sck;
    BME_MISO = miso;
    BME_MOSI = mosi;
    BME_CS = cs;

    Adafruit_BME680 _bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK);
    bme = _bme;
}

bool inventoneBME680::setupBME680() {
    
    bme.begin();
    bme.setTemperatureOversampling(BME680_OS_8X);
    bme.setHumidityOversampling(BME680_OS_2X);
    bme.setPressureOversampling(BME680_OS_4X);
    bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
    bme.setGasHeater(320, 150); // 320*C for 150 ms

    return true;
}

float inventoneBME680::getTemperature() {
    float temp;
    bme.performReading();
    temp = bme.readTemperature();
    return temp;
}

float inventoneBME680::getPressure() {
    float pressure;
    bme.performReading();
    pressure = bme.readPressure() / 100.0F;
    return pressure;
}

float inventoneBME680::getAltitude() {
    float altitude;
    bme.performReading();
    altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
    return altitude;
}

float inventoneBME680::getHumidity() {
    float humidity;
    bme.performReading();
    humidity = bme.readHumidity();
    return humidity;
}