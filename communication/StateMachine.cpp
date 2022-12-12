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
StateMachine::StateMachine() {
    //DEFAULT constructor
    StateMachine(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13);
}
StateMachine::StateMachine(int servo_pin_L, int servo_pin_R, int m_pin_1_L, int m_pin_2_L, int m_pin_1_R, int m_pin_2_R, int enc1_L, int enc2_L, int enc1_R, int enc2_R, int s_pin_L, int s_pin_R, int num_bars) {
    //store the motor objects in the class attributes
    motors = Motors(servo_pin_L, servo_pin_R, m_pin_1_L, m_pin_2_L, m_pin_1_R, m_pin_2_R, enc1_L, enc2_L, enc1_R, enc2_R);

    //store the electromagnet objects
    eMagLeft = Electromagnet(s_pin_L);
    eMagRight = Electromagnet(s_pin_R);

    //initialize system to be in the zero state
    state = 0;

    //set the number of bars traversed to be zero
    barCounter = 0;

    //set the number of total bars
    numBars = num_bars;

    //set the time constants
    tInter = 1500; //intermediate stopping time between swings in ms.    
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
            the start button has been engaged. If bar count exceeds total bars, go to state 6 (terminal).
            */

            Serial.println("hi");
            //update the desired states
            updateDesStates();

            //First, ensure that both electromagnets are on
            eMagLeft.switchOn();
            eMagRight.switchOn();

            if (firstRound == true) {
                firstRound = false; //set it such that it is not the first traversal
                delay(100000);
            } else {
                //delay for tInter seconds. This is a debugging feature that may be shortened in period.
                delay(tInter);
            }
            
            if (barCounter >= numBars) {
                //go to the terminal state, as the number of bars have been met
                state = 6;
            } else {
                //go to state 2 and swing to the next bar
                state = 1;
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
            5. Wrist goes to flop position.

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

            callCounter ++;
            if (callCounter >= callCutoff) {
                //reset the call counter
                callCounter = 0;

                //move to the next state
                state = 2;
            }
            break;

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

            callCounter ++;
            if (callCounter >= callCutoff) {
                //reset the call counter
                callCounter = 0;
                //move to the next state
                state = 3;
            }
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
            
            //wait on the bar for tInter seconds
            delay(tInter);

            if (barCounter >= numBars) {
                //go to the terminal state, as the number of bars have been met
                state = 6;
            } else {
                //go to state 2 and swing to the next bar
                state = 4;
                barCounter++; //increment the bar counter
            }
            break;

        case 4:
             /* FIRST part of a swing
            In state 1, the following parameters are satisfies
            1. Right arm is moving slightly back to avoid hitting the bar
            2. Left arm stays still.
            3. Right electromagnets are off
            4. Left electromagnets are on.
            5. Move right wrist to "flop" configuration

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

            callCounter ++;
            if (callCounter >= callCutoff) {
                //reset the call counter
                callCounter = 0;
                //move to the next state
                state = 5;
            }
            break;

        case 5:
            /* SECOND part of a swing
            In state 4, the following parameters are satisfies
            1. Right arm is moving freely forwards
            2. Left arm is attached to a bar and moving to the backwards position
            3. Right electromagnets are on
            4. Left electromagnets are on.

            Entrance conditions:
            - Case 5 may be entered only from case 4.

            Exit conditions:
            - Case 5 exits after a time period tSwing of seconds has passed and the electromagnet is in position. (moves to case 0)
            */

            //update the desired states
            updateDesStates();

            //turn the left electromagnet on
            eMagLeft.switchOn();

            //turn the right electromagnet on
            eMagRight.switchOn();

            callCounter ++;
            if (callCounter >= callCutoff) {
                //reset the call counter
                callCounter = 0;
                //move to the next state
                state = 0;
            }
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

void StateMachine::state0() {
    Serial.println("hi");
    //update the desired states
    updateDesStates();

    //First, ensure that both electromagnets are on
    eMagLeft.switchOn();
    eMagRight.switchOn();

    if (firstRound == true) {
        firstRound = false; //set it such that it is not the first traversal
        delay(100000);
    } else {
        //delay for tInter seconds. This is a debugging feature that may be shortened in period.
        delay(tInter);
    }
}

void StateMachine::state1() {
    //update the desired states
    updateDesStates();
    
    //turn the left electromagnet off
    eMagLeft.switchOff();

    //turn the right electromagnet on
    eMagRight.switchOn();
}

void StateMachine::state2() {
    //update the desired states
    updateDesStates();

    //turn the left electromagnet on.
    eMagLeft.switchOn();

    //turn the right electromagnet on (should already be on)
    eMagRight.switchOn();
}
void StateMachine::state3() {
    //update the desired states
    updateDesStates();
    
    //turn the left electromagnet on
    eMagLeft.switchOn();

    //turn the right electromagnet on
    eMagRight.switchOn();
    
    //wait on the bar for tInter seconds
    delay(tInter);
}
void StateMachine::state4() {
    //update the desired states
    updateDesStates();
    
    //turn the left electromagnet on
    eMagLeft.switchOn();

    //turn the right electromagnet off
    eMagRight.switchOff();
}
void StateMachine::state5() {
    updateDesStates();

    //turn the left electromagnet on
    eMagLeft.switchOn();

    //turn the right electromagnet on
    eMagRight.switchOn();
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
        //set desired motor states
        motors.setDesPos(backwardSlightServoL, forwardServoR, backwardSlightDCL, forwardDCR);
    } else if (state == 1) {
        //set the desired motor states
        motors.setDesPos(backwardFullServoL, forwardServoR, backwardFullDCL, forwardDCR);
    } else if (state == 2) {
        //set the desired motor states
        motors.setDesPos(forwardServoL, backwardSlightDCR, forwardDCL, backwardSlightDCR);
    } else if (state == 3) {
        //set the desired motor states
        motors.setDesPos(forwardServoL, backwardSlightDCR, forwardDCL, backwardSlightDCR);
    } else if (state = 4) {
        //set the desired motor states
        motors.setDesPos(forwardDCL, backwardFullDCR, forwardDCL, backwardFullDCR);
    } else {
        //set the desired DC states to be whatever they currently are
        return; 
    }
}
