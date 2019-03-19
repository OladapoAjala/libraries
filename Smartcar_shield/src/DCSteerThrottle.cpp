#include "Smartcar.h"

DCSteerThrottle::DCSteerThrottle() { //class to programmatically represent steering with stand alone (or attached to the shield) brushed dc motors for both throttling and steering
    setDegrees();
    setAllowedAngles();
    setFreqsAndSpeeds();
    setAllowedSpeedLimits();
}

void DCSteerThrottle::setDegrees(){
    STRAIGHT_RAW_DEGREES = 90;
    MAX_RIGHT_RAW_DEGREES = 180;
    MAX_LEFT_RAW_DEGREES = 0;
    _angle = STRAIGHT_RAW_DEGREES;
}

void DCSteerThrottle::setFreqsAndSpeeds(){
    FULL_FORWARD = 100;
        FULL_BACKWARD = 100;
    IDLE_RAW_SPEED = 0;
    MAX_FRONT_RAW_SPEED = 255;
    MAX_BACK_RAW_SPEED = -255;
    _speed = IDLE_RAW_SPEED;
}

void DCSteerThrottle::attach(unsigned short directionPinA, unsigned short directionPinB, unsigned short enablePin){
    _motor.attach(directionPinA, directionPinB, enablePin); //whichever of the direction pins goes high and the other low the motor spins towards
}

void DCSteerThrottle::setSpeed(int speed){ //receives a speed in the scale of -100 to 100
    speed = filterSpeed(speed); //speed now holds a value between MAX_BACK_ALLOWED_SPEED and MAX_FRONT_ALLOWED_SPEED (a signed PWM value)
    if (speed > 0){
        _motor.setDirection(FORWARD);
    }else if (speed < 0){
        _motor.setDirection(BACKWARD);
    }else{
        _motor.setDirection(IDLE);
    }
    _motor.setSpeed(abs(speed)); //write the appropriate PWM signal, which is the absolute value of the speed
}


void DCSteerThrottle::setAngle(int degrees){// receives some degrees in the scale of MAX_LEFT_ANGLE, MAX_RIGHT_ANGLE. In this case, the degrees do not represent an actual angle, but the speed according to which the dc motor controlling the steering will be spinning
    if (degrees > 0){ //if positive degrees, let the motor spin "forward" to turn the wheels towards the right
        _motor.setDirection(FORWARD);
    }else if (degrees < 0){ //otherwise, they should spin "backward" towards the left
        _motor.setDirection(BACKWARD);
    }else{  //if the supplied degrees was 0 then the motor should not be turning (therefore remaining straight)
        _motor.setDirection(IDLE);
    }
    //if degrees is not 0, turn steering motor at full speed (at the previously specified direction) to put the wheels into a turning position
    unsigned short speed = (degrees ? MAX_FRONT_RAW_SPEED : IDLE_RAW_SPEED); //otherwise have them being idle
    _motor.setSpeed(speed); //speed will be a PWM signal with full duty cycle if the car should turn and 0 otherwise
}
