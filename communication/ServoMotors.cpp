#include "ServoMotors.h"
/*
This file contains an implementation of the ServoMotors class
*/

/*
Init function for a servo motor.
Inputs:
    servo_pin_L (int) : PWM pin used to control the left servo motor
    servo_pin_R (int) : PWM pin used to control the right servo motor
*/
ServoMotors::ServoMotors() {
    //DEFAULT constructor
    ServoMotors(27, 33);
}

ServoMotors::ServoMotors(int servo_pin_L, int servo_pin_R) {
    //define the servo pin
    servoPinL = servo_pin_L;
    servoPinR = servo_pin_R;

    //set the pin modes to OUTPUT
    pinMode(servoPinL, OUTPUT);
    pinMode(servoPinR, OUTPUT);

    //set the default desired servo positions, 60 degrees (vertical)
    // desPosL = 60;
    // desPosR = 60;

    //define frequencies
    servoFreqLow = 500; //500 for the Pololu servo
    servoFreqHigh = 2500; //2500 for the Pololu servo
    
    //allocate the timers
    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);   

    //set the servo periods
    servoL.setPeriodHertz(50); 
    servoR.setPeriodHertz(50);

    //attach the servos to their PWM pins
    servoL.attach(servoPinL, servoFreqLow, servoFreqHigh);
    servoR.attach(servoPinR, servoFreqLow, servoFreqHigh);
}

/*
Function to set the desired positions of the two servo motors.
Inputs:
    des_pos_1 (int) : desired position in radians of the first servo
    des_pos_2 (int) : desired position in radians of the second servo
*/
void ServoMotors::setDesPos(int des_pos_L, int des_pos_R) {
    desPosL = des_pos_L;
    desPosR = des_pos_R;
}

/*
Function to drive the servo motors to the desired position stored in the class
*/
void ServoMotors::driveDes() {
    driveMotors(desPosL, desPosR);
    return;
}

/*
Function to reset the servo timers. To be used only if servo and DC
are run on the same board.
*/
void ServoMotors::resetTimers() {
    //allocate the timers
    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);   

    //set the servo periods
    servoL.setPeriodHertz(50); 
    servoR.setPeriodHertz(50);

    //attach the servos to their PWM pins
    servoL.attach(servoPinL, servoFreqLow, servoFreqHigh);
    servoR.attach(servoPinR, servoFreqLow, servoFreqHigh);
    return;
}

/*
Function to drive the two servo motors
Inputs:
    desPos1 (int) : desired position from 0 to 180 of the first servo
    desPos2 (int) : desired position from 0 to 180 of the second servo
*/
void ServoMotors::driveMotors(int desPosL, int desPosR) {
    //drive the first servo motor to desPos1
    servoL.write(desPosL);
    //derive the second servo motor to desPos2
    servoR.write(desPosR);
    return;
}

/*
Functions to get the angles of the two servo motors.
Retrieves values from class paramterss.
*/
int ServoMotors::getDesAngleL() {
    //retrieve the desired angle of the first servo
    return desPosL;
}
int ServoMotors::getDesAngleR() {
    //retrieve the desired angle of the second servo
    return desPosR;
}

/*
Servo motor test function. Writes a desired angle to the servo motors that updates in a loop.
To be called repeatedly in the loop() function.
*/
void ServoMotors::servoTest() {
    //drive the servo to an angle (is initialized at zero)
    setDesPos(60, 0);
    driveDes();
    // //now, move between 60 and 80 degrees on each
    // for (int i = 60; i <= 80; i++) {
    //     driveMotors(i, i);
    //     delay(15);
    // }
    // //move backwards
    // for (int i = 80; i>= 60; i--) {
    //     driveMotors(i, i);
    //     delay(15);
    // }
}