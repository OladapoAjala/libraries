#include "Smartcar.h"

const unsigned short SRF08::DEFAULT_PING_DELAY = 70;
const unsigned short SRF08::DEFAULT_SRF08_ADDRESS = 112;

static unsigned short FIRST_ADDRESS = 112; //please refer to: http://www.robot-electronics.co.uk/htm/srf08tech.html
static unsigned short LAST_ADDRESS = 127;

SRF08::SRF08(){
    _address = 0, _delay = 0; //some initial invalid values
}

void SRF08::attach(unsigned short address){
    Wire.begin();
    _address = constrain(address, FIRST_ADDRESS, LAST_ADDRESS); //allow only valid values, between 112 and 127
    _delay = DEFAULT_PING_DELAY;
}

void SRF08::setGain(unsigned short gainValue){
    Wire.beginTransmission(_address); //start i2c transmission
    Wire.write(0x01); //write to GAIN register (1)
    Wire.write(constrain(gainValue,0,31)); //write the value
    Wire.endTransmission(); //end transmission
}

void SRF08::setRange(unsigned short rangeValue){
    Wire.beginTransmission(_address); //start i2c transmission
    Wire.write(0x02); //write to range register (1)
    Wire.write(rangeValue); //write the value -> Max_Range = (rangeValue * 3.4) + 3.4 in centimeters
    Wire.endTransmission(); //end transmission
}

void SRF08::setPingDelay(unsigned short milliseconds){
    _delay = milliseconds;
}

unsigned int SRF08::getDistance(){
    Wire.beginTransmission(_address);
    Wire.write(byte(0x00));
    Wire.write(byte(0x51));
    Wire.endTransmission();
    delay(_delay);
    Wire.beginTransmission(_address);
    Wire.write(byte(0x02));
    Wire.endTransmission();
    Wire.requestFrom(_address, uint8_t (2));
    if (!Wire.available()) return -1; // Return a large error-like value
    byte high = Wire.read();
    byte low = Wire.read();
    return (high << 8) + low;
}

unsigned short SRF08::getLightReading(){
    Wire.beginTransmission(_address);
    Wire.write(byte(0x00));
    Wire.write(byte(0x51));
    Wire.endTransmission();
    delay(_delay);
    Wire.beginTransmission(_address);
    Wire.write(byte(0x01));
    Wire.endTransmission();
    Wire.requestFrom(_address, uint8_t (1));
    if (!Wire.available()) return -1; // Return a large error-like value
    return Wire.read();
}

void SRF08::changeAddress(unsigned short newAddress){
    newAddress = constrain(newAddress, FIRST_ADDRESS, LAST_ADDRESS); //allow only valid values, between 112 and 127
    Wire.beginTransmission(_address);
    Wire.write(byte(0x00));
    Wire.write(byte(0xA0));
    Wire.endTransmission();

    Wire.beginTransmission(_address);
    Wire.write(byte(0x00));
    Wire.write(byte(0xAA));
    Wire.endTransmission();

    Wire.beginTransmission(_address);
    Wire.write(byte(0x00));
    Wire.write(byte(0xA5));
    Wire.endTransmission();

    Wire.beginTransmission(_address);
    Wire.write(byte(0x00));
    Wire.write(newAddress << 1);
    Wire.endTransmission();

    _address = newAddress;
}
