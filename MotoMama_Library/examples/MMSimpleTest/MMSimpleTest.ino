/** @file    MMSimpleTest.h
 *  @author  Jorge Villalobos Carvajal (jorgemvc@gmail.com)
 *  @date    19.Abr.2018  
 *  @version 1.0 
 *  
 *  @brief   Libray for easy usage of MotoMama H-Bridge.
 *
 *  @licence  MIT License
 */
// ---- Libraries
#include <MotoMamaLib.h>

// ---- Variables
MotoMamaLib Robot;

void setup() {
  Robot.begin();
  Robot.setSpeed(175, 175);
}  // void setup

void loop() {
  Robot.forward(1000);
  left90();
  right90();
  Robot.backward(1000);
  delay(1000);
} // void loop

/**
 * @brief  Turns left in 90 degrees
 * 
 * @return void
 */
  void left90(){
  int l, r;
  l = Robot.leftSpeed;
  r = Robot.rightSpeed;

  Robot.setSpeed(175, 175);
  Robot.left(250);

  Robot.stop();
  Robot.setSpeed(l, r);
  delay(200);
}  // void left90

/**
 * @brief  Turns right in 90 degrees
 * 
 * @return void
 */
void right90(){
  int l, r;
  l = Robot.leftSpeed;
  r = Robot.rightSpeed;

  Robot.setSpeed(175, 175);
  Robot.right(250);

  Robot.stop();
  Robot.setSpeed(l, r);
  delay(200);
}  // void right90
