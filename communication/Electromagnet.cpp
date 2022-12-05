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
    //store the signal pin
    sPin = s_pin;
}

/*
Function to turn the electromagnet on. Writes the signal relay pin to high
*/
Electromagnet::switchOn() {
    digitalWrite(sPin, HIGH);
}

/*
Function to turn the electromagnet off. Writes the signal relay pin to low.
*/
Electromagnet::switchOff() {
    digitalWrite(sPin, LOW);
}