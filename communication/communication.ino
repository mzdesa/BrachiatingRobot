#include "Electromagnet.h"
#include "Motors.h"
#include "StateMachine.h"

/*
 * This file currently contains unit tests for the arduino libraries written.
 * Note: default constructors are currently not working, do not use them.
 */

//create an electromagnet object
Electromagnet emagL(17);
Electromagnet emagR(21);

//Create a master Motors object to deal with all motors
Motors motors(33, 27, 13, 12, 15, 32, 34, 39, 26, 25);

int numBars = 2;

//Store desired states for each stage
int forwardServoR = 41; //right front, left back
int forwardServoL = 76; //left front, back right position
int backwardFullServoR = 90; //in this position, it's winding back to avoid hitting a bar.
int backwardFullServoL = 20;
int backwardSlightServoR = 76; //In this position, it's sitting on a bar
int backwardSlightServoL = 41;
int forwardDCR = 0; //right arm forward, left arm back
int forwardDCL = 942; //DC motor position when left arm is forward, WRT a zero at left back
int backwardFullDCR = 534; //don't really care about wrist at full back position.
int backwardFullDCL = -1593;
int backwardSlightDCR = 1045; //DC motor position when right arm sits back on a bar
int backwardSlightDCL = 0;
int flopL = 534; //flop back angle to minimze the profile of the electromagnet
int flopR = -1593;
int tInter = 1500;

//Create a state machine object
//StateMachine stateMachine(motors, emagL, emagR, numBars);

void setup() {
  //Begin a serial monitor
  Serial.begin(115200);
  Serial.println("Starting");
}

void loop() {
  hangTest();
  
//  //first, go to state 0
//  //First, ensure that both electromagnets are on
//  emagL.switchOn();
//  emagR.switchOn();
//  motors.setDesPos(backwardSlightServoL, forwardServoR, backwardSlightDCL, forwardDCR);
//  //drive the motors appropriately
//  for(int i = 0; i<1000; i++) {
//    motors.driveDes();
//    delay(1);
//  }
//
//  //go to state 1
//  //turn the left electromagnet off
//  emagL.switchOff();
//
//  //turn the right electromagnet on
//  emagR.switchOn();
//
//  motors.setDesPos(backwardFullServoL, forwardServoR, backwardFullDCL, forwardDCR);
//  //drive the motors appropriately
//  for(int i = 0; i<1000; i++) {
//    motors.driveDes();
//    delay(1);
//  }
//
//  //go to state 2
//  //turn the left electromagnet on.
//  emagL.switchOn();
//
//  //turn the right electromagnet on (should already be on)
//  emagR.switchOn();
//
//  motors.setDesPos(forwardServoL, backwardSlightDCR, forwardDCL, backwardSlightDCR);
//  //drive the motors appropriately
//  for(int i = 0; i<1000; i++) {
//    motors.driveDes();
//    delay(1);
//  }
//
//  //go to state 3
//  //turn the left electromagnet on
//  emagL.switchOn();
//
//  //turn the right electromagnet on
//  emagR.switchOn();
//
//  motors.setDesPos(forwardServoL, backwardSlightDCR, forwardDCL, backwardSlightDCR);
//  //wait on the bar for tInter seconds
//  delay(tInter);
//  //drive the motors appropriately
//  for(int i = 0; i<1000; i++) {
//    motors.driveDes();
//    delay(1);
//  }
//
//  //go to state 4  
//  //turn the left electromagnet on
//  emagL.switchOn();
//
//  //turn the right electromagnet off
//  emagR.switchOff();
//  motors.setDesPos(forwardDCL, backwardFullDCR, forwardDCL, backwardFullDCR);
//  //drive the motors appropriately
//  for(int i = 0; i<1000; i++) {
//    motors.driveDes();
//    delay(1);
//  }
//
//  //go to state 5
//  //turn the left electromagnet on
//  emagL.switchOn();
//
//  //turn the right electromagnet on
//  emagR.switchOn();
//  //drive the motors appropriately
//  for(int i = 0; i<1000; i++) {
//    motors.driveDes();
//    delay(1);
//  }
}


/*
 * Unit test cases
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
