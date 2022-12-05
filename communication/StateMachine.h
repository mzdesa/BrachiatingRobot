#include <Arduino.h> //required to access the arduino functions.
#include <DCMotor.h>
#include <ServoMotors.h>
#include <Trajectory.h>
#include <Electromagnet.h>
/*
This file contains a class for the state machine of the system, which manages the different 
trajectories based on the state of the system.
*/
class StateMachine {
    private:
        int state;
        int barCounter;
        int numBars;
        int tInter;
        DCMotor dcMotorLeft;
        DCMotor dcMotorRight;
        ServoMotors ServoMotors;
        Electromagnet eMagLeft;
        Electromagnet eMagRight;

        //Store desired states for each stage
        int forwardServo = 0;
        int backwardFullServo = 0; //in this position, it's winding back to avoid hitting a bar.
        int backwardSlightServo = 0; //In this position, it's sitting on a bar
        int forwardDC = 0;
        int backwardFullDC = 0;
        int backwardSlightDC = 0;

        void updateDesStates();
    public:
        StateMachine(DCMotor dc_motor_left, DCMotor dc_motor_right, ServoMotors servo_motors, Electromagnet e_mag_left, Electromagnet e_mag_right, int num_bars);
        void updateState();
        int getState(); //retrieve the state of the system
}