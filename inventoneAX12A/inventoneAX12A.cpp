#include "inventoneAX12A.h"

#define OLD_ID 1

inventoneAX12A::inventoneAX12A() {

}

void inventoneAX12A::setupAX12A(long baudrate, unsigned char comPin, HardwareSerial *serialType) {
    ax12a.begin(baudrate, comPin, serialType);
}

bool inventoneAX12A::led(unsigned char ID, bool state) {
    return ax12a.ledStatus(ID, state);
}

bool inventoneAX12A::setupID (unsigned char ID, unsigned char newID) {
    ax12a.setID (ID, newID);
    return true;
}

bool inventoneAX12A::setupBD (unsigned char ID, long baud) {
    ax12a.setBD (ID, baud);
    return true;
}

int inventoneAX12A::rotate(unsigned char ID, bool direction, int speed) {
    ax12a.setEndless(ID, ON);
    return ax12a.turn(ID, direction, speed);
}

int inventoneAX12A::moveTo (unsigned char ID, int position) {
    int degree;
    degree = map(position, 0, 300, 0, 1023);
    ax12a.setEndless(ID, OFF);
    return ax12a.move(ID, degree);
}

int inventoneAX12A::moveTo(unsigned char ID, int position, int speed) {
    int degree;
    degree = map(position, 0, 300, 0, 1023);
    ax12a.setEndless(ID, OFF);
    return ax12a.moveSpeed(ID, degree, speed);
}

int inventoneAX12A::getTemperature (unsigned char ID) {
    return ax12a.readTemperature(ID);
}

int inventoneAX12A::getVoltage(unsigned char ID) {
    return ax12a.readVoltage(ID);
}

int inventoneAX12A::getPosition(unsigned char ID) {
    return ax12a.readPosition(ID);
}

int inventoneAX12A::getSpeed (unsigned char ID) {
    return ax12a.readSpeed(ID);
}

int inventoneAX12A::getLoad (unsigned char ID) {
    return ax12a.readLoad(ID);
}

int inventoneAX12A::setMaximumTorque (unsigned char ID, int maxTorque) {
    return ax12a.setMaxTorque (ID, maxTorque);
}