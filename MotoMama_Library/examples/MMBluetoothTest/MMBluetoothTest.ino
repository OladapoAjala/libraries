/** @file    MMBlueToothTest.h
 *  @author  Jorge Villalobos Carvajal (jorgemvc@gmail.com)
 *  @date    18.Abr.2018  
 *  @version 1.0 
 *  
 *  @brief   Libray for easy usage of MotoMama H-Bridge.
 *           with the Bluetooth Bee v2.0
 *
 *  @licence  MIT License
 */
// ---- Libraries
#include <MotoMamaLib.h>
#include <SoftwareSerial.h>

// ---- Variables
MotoMamaLib Robot;
SoftwareSerial bt(0, 1);  // TX, RX
char   charRead;
String str = "";
int    i, v;

void setup() {
  Robot.begin();
  bt.begin(9600);
}  // void setup

void loop() {
  if (bt.available()) {
    while (bt.available()) {
      charRead = (char)bt.read();
      str += charRead;
    }
    if (str == "l") {
      left90(); // Robot.left();
    } else if (str == "r") {
      right90(); // Robot.right();
    } else if (str == "u") {
      Robot.forward();
    } else if (str == "d") {
      Robot.backward();
    } else if (str == "s") {
      Robot.stop();
    } else if (isDigit(str[0])) {
      i = str.toInt();
      if (i == 0) i = 10;
      v = map(i, 1, 10, 0, 255);
      Robot.setSpeed(v, v);
    }
    str = "";
  }
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
