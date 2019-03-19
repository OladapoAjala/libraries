/*
*    Car.cpp
*/
#include "Smartcar.h"
/* --- CAR --- */

const unsigned short Car::DEFAULT_PID_LOOP_INTERVAL = 80;
const float Car::DEFAULT_KP = 5.0;
const float Car::DEFAULT_KI = 0.0;
const float Car::DEFAULT_KD = 10.0;

const unsigned short MAX_EFFORTS = 2; //amount of efforts to stop reversing the wheels, in case they have already stopped and spin in the opposite direction

const float MAX_BACK_CRUISE_SPEED = -3.0; //how fast the car can drive forward in cruise control mode (meters/sec)
const float MAX_FRONT_CRUISE_SPEED = 3.0; //how fast the car can drive backward in cruise control mode (meters/sec)
const float GO_CRUISE_SPEED = 1.3; //how fast car should move in go(int centimeters) and rotate(int degrees) while on cruise control
const int GO_RAW_SPEED = 70; //how fast car should move in go(int centimeters)  and rotate(int degrees) while NOT on cruise control

Car::Car(const unsigned short shieldOrientation){
    ShieldMotors *shieldMotors = new ShieldMotors(shieldOrientation);
    init(shieldMotors, shieldMotors);
}

Car::Car(ShieldMotors *shieldMotors){
    init(shieldMotors, shieldMotors);
}

Car::Car(SteeringMotor *steering, ThrottleMotor *throttle){
    init(steering, throttle);
}

void Car::init(SteeringMotor *steering, ThrottleMotor *throttle){
    _cruiseControl = false;
    _speed = 0;
    _angle = 0;
    _numOfEncoders = 0;
    _headingAttached = false;
    _pidLoopInterval = DEFAULT_PID_LOOP_INTERVAL;
    _throttle = throttle;
    _steering = steering;
    _lastGroundSpeed = 0, _Kp = DEFAULT_KP, _Ki = DEFAULT_KI, _Kd = DEFAULT_KD;
    _measuredSpeed = 0, _encoders[0] = NULL, _encoders[1] = NULL, _heading = NULL;
    _lastMotorUpdate = 0, _previousDistance = 0, _previousControlledSpeed = 0;
    _previousError = 0, _integratedError = 0;
}

void Car::begin(){
    setup();
}

void Car::begin(HeadingSensor &heading){
    setupHeadingSensor(heading);
    setup();
}

void Car::begin(Odometer &encoder){
    setupOdometer(encoder);
    setup();
}

void Car::begin(Odometer &encoder, HeadingSensor &heading){
    setupOdometer(encoder);
    setupHeadingSensor(heading);
    setup();
}

void Car::begin(Odometer &encoder1, Odometer &encoder2){
    setupOdometer(encoder1);
    setupOdometer(encoder2);
    setup();
}

void Car::begin(Odometer &encoder1, Odometer &encoder2, HeadingSensor &heading){
    setupOdometer(encoder1);
    setupOdometer(encoder2);
    setupHeadingSensor(heading);
    setup();
}

void Car::setupOdometer(Odometer &encoder){
    _encoders[_numOfEncoders] = &encoder;
    _numOfEncoders++; //increase the number of encoders (or the index in the _encoders array)
}

void Car::setupHeadingSensor(HeadingSensor &heading){
    _heading = &heading;
    _headingAttached = true;
}

void Car::setup(){
    _steering->init();
    _throttle->init();
    _throttle->setSpeed(0);
    _steering->setAngle(0);
}

void Car::setSpeed(float newSpeed){
    if (cruiseControlEnabled()){
//    if the speeds are signed differently, stop the car and then set the new speed. Ignore this if the speed is already 0
        if (!almostEqual(_speed,0) && ((newSpeed * _speed) <= 0)) stop();
        _speed = constrain(newSpeed, MAX_BACK_CRUISE_SPEED, MAX_FRONT_CRUISE_SPEED); //set the new speed
    }else{
        _speed = constrain(int(newSpeed), -100, 100); //constrain the speed between the allowed values
        _throttle->setSpeed(_speed); //write the speed to the motors
    }
}

void Car::setAngle(int angle){
    _angle = constrain(angle, _steering->getMaxLeftAngle(), _steering->getMaxRightAngle()); //constrain the value to the permitted valued the user is allowed to supply
    _steering->setAngle(_angle); // apply the new angle
}

void Car::updateMotors(){
    if (cruiseControlEnabled() && (millis() > _lastMotorUpdate + _pidLoopInterval)){
        if (_speed){ //if _speed is 0, we have already made sure the car is stopped. don't try to adjust if car is just drifting
            _measuredSpeed = getEncoderSpeed(); //speed in m/s
            short direction = getEncoderDirection(); // Positive indicates forward, negative backward, 0 not supported by hardware
            // Decide the sign of the measured speed
            if ((direction == 0 && _speed < 0) || (direction < 0)) {
                // If direction readings are not supported by the odometers `(direction == 0)` AND
                // the set speed is negative, we ASSUME (!) that the car is also moving towards
                // the same direction.
                // Alternatively, if direction is supported and is negative, we assign the negative
                // sign to the measured speed value.
                _measuredSpeed *= -1;
            }
            float controlledSpeed = motorPIDcontrol(_previousControlledSpeed, _speed, _measuredSpeed);
            // In case direction readings are not supported by the odometers, we need to
            // ensure that runaway will not occur (see #5) due to our assumption that we
            // are moving at the same direction as our set speed.
            if ((direction == 0) && (controlledSpeed * _measuredSpeed < 0)) {
                // If we are unable to determine the direction of movement AND the PID controller output
                // hints us to move towards the opposite direction, i.e. due to moving faster than we should
                // or the odometers providing faulty readings, then don't try to spin the motors towards
                // the opposite direction and just halt the motoros. This is because we do not have a
                // reliable way to determine whether we are merely slowing down or accelerating towards
                // the wrong (opposite) direction.
                controlledSpeed = 0;
            }
            _throttle->setSpeed(lroundf(controlledSpeed)); //pass the rounded output of the pid as an input to the motors
            _previousControlledSpeed = controlledSpeed; //save the unrounded float output of the pid
            _lastGroundSpeed = getGroundSpeed(); //used in stop()
        }
        _lastMotorUpdate = millis();
    }
}

float Car::motorPIDcontrol(const float previousSpeed, const float targetSpeed, const float actualSpeed){
    float correction = 0;
    float error = targetSpeed - actualSpeed;
    _integratedError += error;
    correction = (_Kp * error) + (_Ki * _integratedError) + (_Kd * (error - _previousError));
    _previousError = error;
    return constrain(previousSpeed + correction, -100, 100);
}

float Car::getGroundSpeed(){ //the ground speed, as measured by the car. we use it to stop() the vehicle
    unsigned long currentDistance = getEncoderDistance();
    unsigned long dX = currentDistance - _previousDistance;
    _previousDistance = currentDistance;
    unsigned long dT = millis() - _lastMotorUpdate;
    float velocity = (float(dX) * 10)/ dT; //output in m/seconds, divide by 100 to turn cm into m and multiply by 1000, to turn ms to sec
    return velocity;
}

void Car::stop(){
    if (!_numOfEncoders || !cruiseControlEnabled()){ //if no encoders attached or not in cruise control mode
        if (!almostEqual(_speed,0)){ //if the speed that we already have is NOT equal to 0 then
            _throttle->setSpeed(-_speed); //move towards opposite direction at _speed (_speed in non cruise control is between -100,100)
            delay(80); //go the opposite direction for a few milliseconds, to make sure we are stopped
        }
    }else{ //try to measure the ground speed and spin the wheels in the opposite direction, until ground speed is 0
        if (!almostEqual(_speed,0) && !almostEqual(_lastGroundSpeed,0)){ //if the last measured speed by getGroundSpeed() and _speed aren't 0
            unsigned short maxSteps = MAX_EFFORTS;
            do{ //_previousControlledSpeed is the (signed) speed we were writing to the motors, produced by the pid controller
                _throttle->setSpeed(-_previousControlledSpeed); //apply the opposite speed to the motors (it's in range of -100,100)
                delay(_pidLoopInterval); //wait for as much as the usual pid loop interval is
            }while(maxSteps-- && (getGroundSpeed() > 0.02)); //if ground speed is practically 0 or we are out of efforts, we should be stopped.
        }
    }
    if (cruiseControlEnabled()){
        enableCruiseControl(_Kp,_Ki,_Kd); //re-initialize the cruise control, se we get rid of previous error and pid output
    }
    _speed = 0; //update the car's _speed to 0 (regardless of mode), since we have stopped
    _throttle->setSpeed(_speed); //release the motors (_speed == 0), as we should be stopped by now
}

float Car::getSpeed(){
    return _speed; //return the speed that was supplied by the user
}

int Car::getAngle(){
    return _angle; //return what the user supplied
}

void Car::enableCruiseControl(float Kp, float Ki, float Kd, unsigned short pidLoopInterval){
    if (!_numOfEncoders) return; //continue only if at least one encoder was attached
    _cruiseControl = true;
    _pidLoopInterval = pidLoopInterval;
    _lastMotorUpdate = 0;
    _previousControlledSpeed = 0;
    _previousDistance = getEncoderDistance();
    _integratedError = 0;
    _Kp = Kp;
    _Ki = Ki;
    _Kd = Kd;
}

void Car::disableCruiseControl(){
    if (cruiseControlEnabled()){
        _cruiseControl = false;
        _speed = _previousControlledSpeed; //update the speed in m/s with the raw (percentage) equivalent
    }
}

boolean Car::cruiseControlEnabled(){
    return _cruiseControl;
}

unsigned long Car::getEncoderDistance(){ //gets the average distance measured by the attached encoders
    unsigned long averageDistance = 0;
    for (int i = 0; i < _numOfEncoders; i++){
        averageDistance += _encoders[i]->getDistance() / _numOfEncoders;
    }
    return averageDistance;
}

float Car::getEncoderSpeed(){ //gets the average speed measured by the attached encoders
    float averageSpeed = 0;
    for (int i = 0; i< _numOfEncoders; i++){
        averageSpeed += _encoders[i]->getSpeed() / _numOfEncoders;
    }
    return averageSpeed;
}

short Car::getEncoderDirection() {
    short direction = 0; // Direction 0 indicates a not supported error
    for (int i = 0; i < _numOfEncoders; i++) {
        short encoderDirection = _encoders[i]->getDirection();
        // Ignore the reading if direction is not supported by the odometer i.e. it's `0`
        if (encoderDirection) {
            // Add up the directions of movement. Overall, if the sum is a positive
            // we can say that we are moving forward and if it is negative backward.
            direction += encoderDirection;
        }
    }
    return direction;
}

void Car::initializeEncoders(){ //initializes the attached encoders
    for (int i = 0; i < _numOfEncoders; i++){
        _encoders[i]->begin();
    }
}

void Car::go(int centimeters){
    if (!_numOfEncoders) return; //continue only if at least one encoder was attached
    unsigned long initialDistance = getEncoderDistance(); //save the current distance the car has covered
    float initialSpeed = getSpeed(); //save the current speed (so we restore it later)
    int initialAngle = getAngle(); //save the current angle (so we restore it later)
    unsigned long targetDistance = initialDistance + abs(centimeters); //how much the car should move, always a positive number
    if (initialDistance > targetDistance){ //this will occur only if the unsigned long variable overflows
        initializeEncoders(); //reinitialize the encoders counter to 0
        targetDistance = abs(centimeters); //now the new target is just the centimeters (since the encoder distance is 0)
    }
    setAngle(0); //set the angle straight
    short direction = 1;
    if (centimeters < 0) direction = -1; //if the user supplied a negative argument, means they want to move backwards
    if (cruiseControlEnabled()){ //depending on whether the cruise control is enabled set the speed
        setSpeed(direction * GO_CRUISE_SPEED);
    }else{
        setSpeed(direction * GO_RAW_SPEED);
    }
    while (getEncoderDistance() < targetDistance){ //while we haven't reached the target distance, keep moving
        if (cruiseControlEnabled()) updateMotors(); //otherwise the pid for the motors won't work
    }
    setSpeed(initialSpeed); //restore to the initial speed
    setAngle(initialAngle); //restore to the inital angle
}
void Car::rotate(int targetDegrees){
        targetDegrees %= 360; //put it on a (-360,360) scale
    if (!_headingAttached || !targetDegrees) return; //continue only if heading sensor is attached and the targetDegrees is not 0
    float initialSpeed = getSpeed(); //save the current speed (so we restore it later)
    int initialAngle = getAngle(); //save the current angle (so we restore it later)
    if (targetDegrees > 0){ //we should turn to the right (clockwise)
        setAngle(_steering->getMaxRightAngle()); //turn right as steep as you can
    }else{ //turn left (counterclockwise)
        setAngle(_steering->getMaxLeftAngle()); //turn left as steep as you can
    }
    if (cruiseControlEnabled()){ //depending on whether the cruise control is enabled set the speed
        setSpeed(GO_CRUISE_SPEED);
    }else{
        setSpeed(GO_RAW_SPEED);
    }
    unsigned int initialHeading = _heading->getAngularDisplacement(); //initial heading used as offset to calculate the absolute displacement
    int degreesTurnedSoFar = 0; //this variable will hold the absolute displacement from the beginning of the rotation
    while (abs(degreesTurnedSoFar) < abs(targetDegrees)){ //while absolute displacement hasn't reached the (absolute) target, keep turning
        if (cruiseControlEnabled()) updateMotors(); //adjust the motor speed with the PID controller
        _heading->update(); //update to integrate the latest heading sensor readings
        int currentHeading = _heading->getAngularDisplacement(); //in the scale of 0 to 360
        if (targetDegrees < 0 && currentHeading > initialHeading){ //if we are turning left and the current heading is larger than the
        //initial one (e.g. started at 10 degrees and now we are at 350), we need to substract 360, so to eventually get a signed
                currentHeading -= 360; //displacement from the initial heading (-20)
        }else if (targetDegrees > 0 && currentHeading < initialHeading){ //if we are turning right and the heading is smaller than the
        //initial one (e.g. started at 350 degrees and now we are at 20), so to get a signed displacement (+30)
                currentHeading += 360;
        }
        degreesTurnedSoFar = initialHeading - currentHeading; //degrees turned so far is initial heading minus current (initial heading
        //is at least 0 and at most 360. To handle the "edge" cases we substracted or added 360 to currentHeading)
    }
    setSpeed(initialSpeed); //restore to the initial speed
    setAngle(initialAngle); //restore to the inital angle
}

void Car::setMotorSpeed(int leftMotorSpeed, int rightMotorSpeed){ //will set the speed manual to each motor, use with caution
    if (cruiseControlEnabled()) return; //we don't want to be manually messing with the speed, during cruise control
    leftMotorSpeed = constrain(leftMotorSpeed, -100, 100); //constrain the speed between the allowed range
    rightMotorSpeed = constrain(rightMotorSpeed, -100, 100);
    _throttle->setMotorSpeed(leftMotorSpeed, rightMotorSpeed);
}
