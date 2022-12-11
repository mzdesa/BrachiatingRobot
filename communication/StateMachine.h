#ifndef StateMachine_H
#define StateMachine_H

#include <Arduino.h> //required to access the arduino functions.
#include "Electromagnet.h"
#include "Motors.h"
/*
This file contains a class for the state machine of the system, which manages the different 
trajectories based on the state of the system.
*/
class StateMachine {
    private:
        int barCounter;
        int numBars;
        int tInter;
        Motors motors;
        Electromagnet eMagLeft;
        Electromagnet eMagRight;

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

        //store information about first traversal
        bool firstRound = true;

        //store a call counter for the number of calls to each feedback loop
        int callCounter = 0;
        int callCutoff = 50; //gives around 1s of motion.

        void updateDesStates();
    public:
        int state;
        StateMachine();
        StateMachine(Motors mtrs, Electromagnet e_mag_left, Electromagnet e_mag_right, int num_bars);
        void updateState();
        void state0();
        void state1();
        void state2();
        void state3();
        void state4();
        void state5();
        int getState(); //retrieve the state of the system
};

#endif