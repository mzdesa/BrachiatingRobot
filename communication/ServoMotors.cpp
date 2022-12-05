#include "ServoMotors.h"
/*
This file contains an implementation of the ServoMotors class
*/

/*
Init function for a servo motor.
Inputs:
    servoPin (int) : PWM pin used to control the servo motor
    allocate
*/
ServoMotors::ServoMotors(int servo_pin) {
    //define the servo pin
    servoPin = servo_pin;
    
    //allocate the timers
    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);   

    //set the servo periods
    servoL.setPeriodHertz(50); 
    servoR.setPeriodHertz(50);

    //attach the servos to their PWM pins
    servo1.attach(servoPinL, servoFreqLow, servoFreqHigh);
    servo2.attach(servoPinR, servoFreqLow, servoFreqHigh);
}

/*
Function to set the desired positions of the two servo motors.
Inputs:
    des_pos_1 (double) : desired position in radians of the first servo
    des_pos_2 (double) : desired position in radians of the second servo
*/
ServoMotors::setDesPos(double des_pos_L, double des_pos_R) {
    desPosL = des_pos_L;
    desPosR = des_pos_R;
}

/*
Function to drive the servo motors to the desired position stored in the class
*/
ServoMotors::driveDes() {
    driveMotors(desPosL, desPosR);
}

/*
Function to reset the servo timers. To be used only if servo and DC
are run on the same board.
*/
ServoMotors::resetTimers() {
    //allocate the timers
    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);   

    //set the servo periods
    servoL.setPeriodHertz(50); 
    servoR.setPeriodHertz(50);
}

/*
Function to drive the two servo motors
Inputs:
    desPos1 (int) : desired position from 0 to 180 of the first servo
    desPos2 (int) : desired position from 0 to 180 of the second servo
*/
ServoMotors::driveMotors(int desPosL, int desPosR) {
    //drive the first servo motor to desPos1
    servo1.write(desPosL);
    //derive the second servo motor to desPos2
    servo2.write(desPosR);
}

/*
Functions to get the angles of the two servo motors.
Retrieves values from class paramterss.
*/
ServoMotors::getDesAngleL() {
    //retrieve the desired angle of the first servo
    return desPosL;
}
ServoMotors::getDesAngleR() {
    //retrieve the desired angle of the second servo
    return desPosR;
}
