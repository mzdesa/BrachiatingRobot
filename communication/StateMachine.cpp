#include "StateMachine.h"
/*
This file contains an implementation of the State Machine class
*/

/*
Initialization function for a state machine
Inputs:
    dc_motor_left (DCMotor) : DC motor object, left arm
    dc_motor_right (DCMotor) : DC motor object, right arm
    servo_motors (ServoMotors) : Servo motors (L and R) object
    num_bars (int) : number of total bars on the monkey bars
*/
StateMachine::StateMachine(DCMotor dc_motor_left, DCMotor dc_motor_right, ServoMotors servo_motors, Electromagnet e_mag_left, Electromagnet e_mag_right, int num_bars) {
    //store the motor objects in the class attributes
    dcMotorLeft = dc_motor_left;
    dcMotorRight = dc_motor_right;
    servoMotors = servo_motors;

    //store the electromagnet objects
    eMagLeft = e_mag_left;
    eMagRight = e_mag_right;

    //initialize system to be in the zero state
    state = 0;

    //set the number of bars traversed to be zero
    barCounter = 0;

    //set the number of total bars
    numBars = num_bars;

    //set the time constants
    tInter = 5000; //intermediate stopping time between swings in ms.
}

/*
Function to update the state based on the current values of the system
*/
void StateMachine::updateState() {
    //Finite state machine switch statement
    switch (state) {
        case 0:
            /*
            Case 0 is the initialization state. In state 0, the following parameters are satisfied:
            1. The right arm is in the forwards position on a bar, the left arm is in the backwards 
               position on a bar. 
            2. The electromagnets on both arms are on.
            3. Increment bar count by 1.
            
            Entrance conditions:
                ...
            Exit conditions:
            This state is only visited for tInter time. It is the start state of the system and is exited once
            the start button has been engaged. If bar count exceeds total bars, go to state 4.
            */

            //update the desired states
            updateDesStates();

            //First, ensure that both electromagnets are on
            eMagLeft.switchOn();
            eMagRight.switchOn();

            //delay for tInter seconds. This is a debugging feature that may be shortened in period.
            delay(tInter);

            if (barCounter >= numBars) {
                //go to the terminal state, as the number of bars have been met
                state = 4;
            } else {
                //go to state 2 and swing to the next bar
                state = 2;
                barCounter++; //increment the bar counter
            }
            break;
        
        case 1:
             /* FIRST part of a swing
            In state 1, the following parameters are satisfies
            1. Right arm is not moving.
            2. Left arm has detached from the bar and is moving backwards slightly to avoid hitting the bar.
            3. Right electromagnets are on
            4. Left electromagnets are off.

            Entrance conditions:
            - Case 1 may be entered only from case 0.

            Exit conditions:
            - Case 1 exits after a time period tSwing of seconds has passed and the left arm has moved sufficiently far back. (moves to case 2)
            */

            //update the desired states
            updateDesStates();
           
            //turn the left electromagnet off
            eMagLeft.switchOff();

            //turn the right electromagnet on
            eMagRight.switchOn();

        case 2:
            /* SECOND part of a swing
            In state 2, the following parameters are satisfies
            1. Right arm is moving to the backwards position and attached to a bar
            2. Left arm has detached from the bar and is moving forwards
            3. Right electromagnets are on
            4. Left electromagnets are on.

            Entrance conditions:
            - Case 1 may be entered only from case 0.

            Exit conditions:
            - Case 1 exits after a time period tSwing of seconds has passed and the electromagnet is in position. (moves to case 3)
            */

            //update the desired states
            updateDesStates();

            //turn the left electromagnet on.
            eMagLeft.switchOn();

            //turn the right electromagnet on (should already be on)
            eMagRight.switchOn();
            break;
        case 3:
            /*
            In state 3, the following parameters are satisfied:
            1. The right arm is in the backwards position on a bar
            2. Left arm is in the forwards position on a bar
            3. Right electromagnets are on
            4. Left electromagnets are on
            5. Increment bar count by 1
            Entrance conditions:
            - Case 3 may be enetered only from case 2
            Exit conditions:
            - Case 3 is exited a time tInter after entrance to prepare for the next swing.
            - Case 3 is exited to state 4 if the bar count exceeds number of bars
            */

            //update the desired states
            updateDesStates();
            
            //turn the left electromagnet on
            eMagLeft.switchOn();

            //turn the right electromagnet on
            eMagRight.switchOn();
            break;

        case 4:
             /* FIRST part of a swing
            In state 1, the following parameters are satisfies
            1. Right arm is moving slightly back to avoid hitting the bar
            2. Left arm stays still.
            3. Right electromagnets are off
            4. Left electromagnets are on.

            Entrance conditions:
            - Case 4 may be entered only from case 3.

            Exit conditions:
            - Case 1 exits after a time period tSwing of seconds has passed and the left arm has moved sufficiently far back. (moves to case 2)
            */

            //update the desired states
            updateDesStates();
           
            //turn the left electromagnet on
            eMagLeft.switchOn();

            //turn the right electromagnet off
            eMagRight.switchOff();

        case 5:
            /* SECOND part of a swing
            In state 4, the following parameters are satisfies
            1. Right arm is moving freely forwards
            2. Left arm is attached to a bar and moving to the backwards position
            3. Right electromagnets are on
            4. Left electromagnets are on.

            Entrance conditions:
            - Case 4 may be entered only from case 3.

            Exit conditions:
            - Case 1 exits after a time period tSwing of seconds has passed and the electromagnet is in position. (moves to case 3)
            */

            //update the desired states
            updateDesStates();

            //turn the left electromagnet on
            eMagLeft.switchOn();

            //turn the right electromagnet on
            eMagRight.switchOn();
            break;

        case 6:
            /*
            In case 4, the following parameters are satisfied:
            1. The right arm is fixed to a bar
            2. The left arm is fixed to a bar
            3. Right electromagnets are on
            4. Left electromagnets are on
            5. The bar count exceeds or equals the number of monkey bars.
            Entrance conditions:
            - State is entered if bar count exceeds or equals number of bars, from case 0 or case 2.
            Exit conditions:
            - Robot must be reset to exit case 4, this is the terminal case
            */
           eMagLeft.switchOn();
           eMagRight.switchOn();
           break;
    }
}

/*
Function to retrieve the state of the system
*/
int StateMachine::getState() {
    return state;
}

/*
Function to update the desired states of each motor depending on the state
*/
void StateMachine::updateDesStates() {
    if (state == 0) {
        //set the desired DC states
        dcMotorRight.setDesPos(forwardDC);
        dcMotorLeft.setDesPos(backwardSlightDC);

        //set the desired servo states
        servoMotors.setDesPos(backwardSlightServo, forwardServo);

    } else if (state == 1) {
        //set the desired DC states
        dcMotorRight.setDesPos(forwardDC);
        dcMotorLeft.setDesPos(backwardFullDC);

        //set the desired servo states
        servoMotors.setDesPos(backwardFullServo, forwardServo);
    } else if (state == 2) {
        //set the desired DC states
        dcMotorRight.setDesPos(backwardSlightDC);
        dcMotorLeft.setDesPos(forwardDC);

        //set the desired servo states
        servoMotors.setDesPos(forwardServo, backwardSlightDC);
    } else if (state == 3) {
        //set the desired DC states
        dcMotorRight.setDesPos(backwardSlightDC);
        dcMotorLeft.setDesPos(forwardDC);

        //set the desired servo states
        servoMotors.setDesPos(forwardServo, backwardSlightDC);
    } else if (state = 4) {
        //set the desired DC states
        dcMotorRight.setDesPos(backwardFullDC);
        dcMotorLeft.setDesPos(forwardDC);

        //set the desired servo states
        servoMotors.setDesPos(forwardDC, backwardFullDC);
    } else {
        //set the desired DC states to be whatever they currently are
        return; 
    }
}