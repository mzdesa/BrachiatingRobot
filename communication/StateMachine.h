#include <Arduino.h> //required to access the arduino functions.
#include <DCMotor.h>
#include <ServoMotors.h>
#include <Trajectory.h>
/*
This file contains a class for the state machine of the system, which manages the different 
trajectories based on the state of the system.
*/
class StateMachine {
    private:
        int state;
        DCMotor dcMotor;
        ServoMotors ServoMotors;
    public:
        StateMachine(DCMotor dc_motor, ServoMotors servo_motors);
        void updateState();
}