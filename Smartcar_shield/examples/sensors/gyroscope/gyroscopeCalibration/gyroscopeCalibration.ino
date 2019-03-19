#include <Smartcar.h>

Gyroscope gyro;

void setup() {
  gyro.attach();
  Serial.begin(9600);
  delay(1500);
  gyro.begin();
  Serial.println("Calibrating gyroscope, this might take some seconds");
  int offset = gyro.calibrate();
  Serial.print("This gyro's offset value is: ");
  Serial.println(offset);
  Serial.print("Please initialize Gyroscope with the above value as: Gyroscope gyro(");
  Serial.print(offset);
  Serial.println("); or another similar value that works better according to your experimentation.");
}

void loop() {
}
