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
Function to turn the electromagnet on. To turn the electromagnet on, set the 
EN pin on the A4988 driver to LOW using the GPIO sPin.
*/
void Electromagnet::switchOn() {
    digitalWrite(sPin, LOW);
}

/*
Function to turn the electromagnet off. To turn the electromagnet off, set the
EN pin on the A4988 driver to HIGH using the GPIO sPin.
*/
void Electromagnet::switchOff() {
    digitalWrite(sPin, HIGH);
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
