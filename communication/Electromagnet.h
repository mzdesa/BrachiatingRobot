#ifndef Electromagnet_H
#define Electromagnet_H

#include <Arduino.h> //required to access arduino functionality
/*
This file contains a class for interacting with a single electromagnet, or a set of
electromagnets wired to the same terminal on the relay board.
*/

class Electromagnet {
    private:
        //electromagnet signal pin from the ESP32
        int sPin;
        int testPeriod;
    public:
        Electromagnet(); //define a default constructor
        Electromagnet(int s_pin);
        void switchOn();
        void switchOff();
        void emagTest();
};

#endif