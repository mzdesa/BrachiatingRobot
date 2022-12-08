#include "Electromagnet.h"
#include "ServoMotors.h"
#include "DCMotor.h"
#include "Motors.h"

/*
 * This file currently contains unit tests for the arduino libraries written.
 * Note: default constructors are currently not working, do not use them.
 */

//create an electromagnet object
Electromagnet emagL(17);
Electromagnet emagR(21);

//create a servo object using the default constructor
//ServoMotors servos(27, 33);

//create a DC motor object
//DCMotor motorL(12, 13, 34, 39, 1, 2);
//DCMotor motorR(15, 32, 26, 25, 3, 4);


//Create a master Motors object to deal with all motors
Motors motors(27, 33, 12, 13, 15, 32, 34, 39, 26, 25);

void setup() {
  Serial.begin(115200);
}

void loop() {
  basicTests();
}

void basicTests() {
  //Electromagnet test
//  emagL.emagTest();
//  emagR.emagTest();

  motors.driveServos(60, 60);
  motors.driveOLTest();
  delay(15);
}

void hangTest() {
  //move the servos to a default 60 deg position
//  servos.driveDes();
  
  //turn on the electromagnets for a simple hang
  emagR.switchOn();
  emagL.switchOn();
}
