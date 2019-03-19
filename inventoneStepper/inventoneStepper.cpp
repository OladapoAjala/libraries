#include "inventoneStepper.h"
#include <AccelStepper.h>
#include <AFMotor.h>

#include "Arduino.h"

uint8_t motor_pin1;
uint8_t motor_pin2;
uint8_t motor_pin3;
uint8_t motor_pin4;

AccelStepper stepper(AccelStepper::FULL4WIRE, motor_pin1, motor_pin2, motor_pin3, motor_pin4);

inventoneStepper::inventoneStepper (uint8_t _pin1, uint8_t _pin2, uint8_t _pin3, uint8_t _pin4) {
    AccelStepper _stepper(AccelStepper::FULL4WIRE, _pin1, _pin2, _pin3, _pin4);
    stepper = _stepper;
}

void inventoneStepper::setupMotor (int maxSpeed, int speed, int accel, int position) {
    stepper.setMaxSpeed (maxSpeed);
    stepper.setSpeed (speed);
    stepper.setAcceleration (accel);
    stepper.moveTo (position);
}

void inventoneStepper::turnMotor () {
    stepper.runSpeed();
}