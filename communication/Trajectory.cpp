#include "Trajectory.h"
/*
This file implements the Trajectory class.
*/

/*
Initialize a Trajectory object
*/
Trajectory::Trajectory(DCMotor dc_motor_left, DCMotor dc_motor_right, ServoMotors servo_motors) {
    //store the two DC motors
    dcMotorLeft = dc_motor_left;
    dcMotorRight = dc_motor_right;
    //store the servo motors
    servoMotors = servo_motors;

    //initialize the state to be zero. The state will be updated by the state machine.
    state = 0;
}

/*
Function to update the desired states of each system based on the state machine state.
*/
Trajectory::updateTraj() {
    dcMotorLeft.setDesPos();
    dcMotorRight.setDesPos();
    servoMotors.setDesPos();
}