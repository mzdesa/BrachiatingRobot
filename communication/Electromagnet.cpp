#include "Electromagnet.h"
/*
This file contains an implementation of the Electromagnet class
*/

/*
Initialize an electromagnet object
Inputs:
    s_pin (int) : pin number of signal pin used to switch the electromagnet on and off
*/
Electromagnet::Electromagnet(int s_pin) {
    sPin = s_pin; //store the signal pin
    testPeriod = 3000; //set the test period
}

/*
Function to turn the electromagnet on. To turn the electromagnet on, set the 
EN pin on the A4988 driver to LOW using the GPIO sPin.
*/
Electromagnet::switchOn() {
    digitalWrite(sPin, LOW);
}

/*
Function to turn the electromagnet off. To turn the electromagnet off, set the
EN pin on the A4988 driver to HIGH using the GPIO sPin.
*/
Electromagnet::switchOff() {
    digitalWrite(sPin, HIGH);
}

/*
Function to provide a test case for the electromagnet. Runs the electromagnet high for 
3 seconds, then low for 3 seconds. To be placed in the main loop of an arduino script.
*/
Electromagnet::emagTest() {
    switchOn();
    delay(testPeriod);
    switchOff();
    delay(testPeriod);
}
