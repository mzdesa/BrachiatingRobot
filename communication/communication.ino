#include "Electromagnet.h"
#include "Motors.h"
#include "StateMachine.h"

/*
 * This file currently contains unit tests for the arduino libraries written.
 * Note: default constructors are currently not working, do not use them.
 */
//create electromagnet objects for DEBUGGING ONLY (Comment out when using state machine)
Electromagnet emagL(17);
Electromagnet emagR(21);

//create a motors object for DEBUGGING ONLY (Comment out when using state machine)
Motors motors(33, 27, 13, 12, 15, 32, 34, 39, 26, 25);

int numBars = 2;

//Create a state machine object
StateMachine stateMachine(33, 27, 13, 12, 15, 32, 34, 39, 26, 25, 17, 21, numBars);

void setup() {
  //Begin a serial monitor
  Serial.begin(115200);
  Serial.println("Starting");
}

void loop() {  
  //update the state machine state
  stateMachine.updateState();
  //drive the motors to their desired position
  stateMachine.motors.driveDes();
}


/*
 * Unit test cases - to be used for debugging ONLY when the state machine has not been initalized.
 * Place in the main loop() to use.
 * emagTests() -> test case for the electromagnet units on both arms
 * hangTest() -> writes both electromagnets high for a hanging test
 */

void detachTest() {
  //test detaching and arm moving back sequence

  //turn L electromagnet off
  emagL.switchOff();

  //move the left arm back and the left DC motor to flop back position
  motors.setDesPos(20, 41, 534, 0);

  //drive the motors
  motors.driveDes();
}

void servoTests() {
  //run the servo to a desired angle, DC motors to 0.
  int desAngle = 41;
  motors.setDesPos(desAngle, desAngle, 300, -300);
  motors.driveDes();
  Serial.println(motors.getAngleMotorLeft());
  Serial.println(motors.getAngleMotorRight());
  delay(15);
}

void dcTests() {
  //digitalWrite(13, HIGH);
  //digitalWrite(12, LOW);
  motors.setDesPos(60, 60, 300, 300);
  motors.driveDCR(300);
  motors.driveDCL(300);
  printEncoder();
}

void encoderTest() {
  //print the encoder readings to the serial monitor
  Serial.println(motors.getAngleMotorLeft());
  Serial.println(motors.getAngleMotorRight());
}

void emagTests() {
  //Run the electromagnet tests
  emagL.emagTest();
  emagR.emagTest();
}

void hangTest() {
  //move the servos to a default 41 deg position
  motors.setDesPos(60, 60, 0, 0);
  motors.driveDes();
  
  //turn on the electromagnets for a simple hang
  emagR.switchOn();
  emagL.switchOn();

  printEncoder();
}

void printEncoder() {
  Serial.print("enc left: ");
  Serial.print(motors.getAngleMotorLeft());
  Serial.println();
  Serial.print("enc right: ");
  Serial.print(motors.getAngleMotorRight());
  Serial.println();
}

void encoder41Deg() {
  //Start in the 41, 41 position with both wrists vertical. this is the zero position.
  //(41, 41) is left arm forwards, left arm backwards.  
  motors.setDesPos(41, 41, 0, 0);

  motors.driveDes();
}

void encoderCalibrate() {
  //to be called AFTER setup()
  //move to the 76, 76 position. (76, 76) is left arm forwards, right arm backwards.
  motors.setDesPos(76, 76, 0, 0);
  motors.driveDes();
  //Now, move the wrists to vertical in this config and print out the encoder reading.
  //This gives desired state.
  printEncoder();
}
