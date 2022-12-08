#include "Electromagnet.h"
#include "ServoMotors.h"

/*
 * This file currently contains unit tests for the arduino libraries written.
 * Note: default constructors are currently not working, do not use them.
 */

//create an electromagnet object
Electromagnet emag(13);

//create a servo object using the default constructor
ServoMotors servos(27, 33);

void setup() {
  
}

void loop() {
  //Electromagnet test
  //emag.emagTest();

  //Servo motor test
  servos.servoTest();
}
