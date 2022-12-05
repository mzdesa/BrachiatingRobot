#include <Arduino.h> //required to access the arduino functions.
#include <DCMotor.h> //DC motor class
#include <ServoMotors.h> //Servo motor class
#include <StateMachine.h> //State machine class
/*
This file contains the utilities necessary to control the trajectory of the robot.
Uses simple setpoint control, with desired states computed based on the 
*/
class Trajectory {
    //Trajectory class should refer to dcMotor and servoMotor objects, as it must set desired states
    private:
        //define DC motor and servo motors
        StateMachine stateMachine;
        int state; //current state of the system
    public:
        Trajectory(StateMachine state_machine);
        void updateTraj(); //will just depend on the state machine state
}