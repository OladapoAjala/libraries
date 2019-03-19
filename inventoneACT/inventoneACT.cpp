#include "inventoneACT.h"
#include "Servo.h"

#include "Arduino.h"

Servo myservo;

inventoneACT::inventoneACT(uint8_t pin) {
    pinMode(pin, OUTPUT);
    myservo.attach(pin);
    _pin = pin;
}

inventoneACT::inventoneACT() {
    delay(10);
}

void inventoneACT::setupForRead(uint8_t pin) {
    pinMode(pin, INPUT);
}

void inventoneACT::setupForWrite(uint8_t pin) {
    pinMode(pin, OUTPUT);
}

void inventoneACT::turnLedOn() {
    digitalWrite (_pin, HIGH);
}

void inventoneACT::turnLedOff() {
    digitalWrite (_pin, LOW);
}

void inventoneACT::turnRelayOn() {
    digitalWrite (_pin, HIGH);
}

void inventoneACT::turnRelayOff() {
    digitalWrite (_pin, LOW);
}

void inventoneACT::rotate(int speed){
    analogWrite (_pin, speed);
}

void inventoneACT::turn(int degrees) {
    myservo.write(degrees);
}

float inventoneACT::multiplex(float data1, float data2, char *condition) {
    
    if (strcmp(condition, ">") == 0 ) {
        if (data1 > data2) {
            return data1;
        }
        else return data2;
    }
    else if (strcmp(condition, ">=") == 0) {
        if (data1 >= data2) {
            return data1;
        }
        else return data2;
    }
    else if (strcmp(condition, "<") == 0) {
        if (data1 < data2) {
            return data1;
        }
        else return data2;
    }
    else if (strcmp(condition, "<=") == 0) {
        if (data1 <= data2) {
            return data1;
        }
        else return data2;
    }

}

float inventoneACT::pass (float input, bool shouldPass) {
    if (shouldPass) {
        return input;
    }
    else return 0;
}

bool inventoneACT::threshold(float data1, float data2, char *condition) {

    if (strcmp(condition, ">") == 0 ) {
        if (data1 > data2) {
            return true;
        }
        else return false;
    }
    else if (strcmp(condition, ">=") == 0) {
        if (data1 >= data2) {
            return true;
        }
        else return false;
    }
    else if (strcmp(condition, "<") == 0) {
        if (data1 < data2) {
            return true;
        }
        else return false;
    }
    else if (strcmp(condition, "<=") == 0) {
        if (data1 <= data2) {
            return true;
        }
        else return false;
    }
}

int inventoneACT::map(long data, long in_min, long in_max, long out_min, long out_max) {
   return (data - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

char* inventoneACT::string(char *text) {
    return text;
}

String inventoneACT::buildText(String text1, float x, String text2) {
    String result;
    result = text1;
    result += x;
    result += text2;

    return result;
}

int inventoneACT::analog_read(uint8_t pin) {
    return analogRead(pin);
}

void inventoneACT::analog_write(uint8_t pin, int value) {
    analogWrite(pin, value);
}

bool inventoneACT::digital_read(uint8_t pin) {
    return digitalRead(pin);
}

void inventoneACT::digital_write(uint8_t pin, int value) {
    digitalWrite(pin, value);
}