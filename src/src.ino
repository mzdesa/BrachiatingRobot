/*
This file contains a series of unit tests to be run for each device in the robot.
*/

//Import the electromagnet class
#include "Electromagnet.h"

//create an electromagnet object
int sPin = 13;
Electromagnet eMag(sPin); //create an electromagnet called eMag at pin 13

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println("hi");
}
