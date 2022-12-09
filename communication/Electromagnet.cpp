#include "Electromagnet.h"
/*
This file contains an implementation of the Electromagnet class
*/

/*
Initialize an electromagnet object
Inputs:
    s_pin (int) : pin number of signal pin used to switch the electromagnet on and off
*/
Electromagnet::Electromagnet() {
    //default constructor - calls the other constructor
    Electromagnet(13);
}

Electromagnet::Electromagnet(int s_pin) {
    sPin = s_pin; //store the signal pin
    testPeriod = 3000; //set the test period

    //set the pin mode to OUTPUT
    pinMode(sPin, OUTPUT);
}

/*
Function to turn the electromagnet on. To turn the electromagnet on, set the forward signal
pin on the L298N Motor driver HIGH.
*/
void Electromagnet::switchOn() {
    digitalWrite(sPin, HIGH);
}

/*
Function to turn the electromagnet off. To turn the electromagnet off, set the forward signal
pin on the L298N Motor driver LOW.
*/
void Electromagnet::switchOff() {
    digitalWrite(sPin, LOW);
}

/*
Function to provide a test case for the electromagnet. Runs the electromagnet high for 
testPeriod ms, then low for testPeriod ms. Place in loop() to test.
*/
void Electromagnet::emagTest() {
    switchOn();
    delay(testPeriod);
    switchOff();
    delay(testPeriod);
}
