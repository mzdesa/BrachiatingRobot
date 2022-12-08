#ifndef ServoMotors_H
#define ServoMotors_H

#include <Arduino.h> //required to access the arduino functions.
#include <ESP32Servo.h> //Servo library
/*
This file contains the utilities for driving BOTH servo motors.
*/
class ServoMotors {
    public:
        ServoMotors(); //default constructor
        ServoMotors(int servo_pin_L, int servo_pin_R);
        void setDesPos(int des_pos_L, int des_pos_R);
        void driveDes();
        void resetTimers();
        int getDesAngleL();
        int getDesAngleR();
        void servoTest();
    private:
        //Define esp32Servo objects
        Servo servoL;
        Servo servoR;

        //PWM pins for the servos
        int servoPinL;
        int servoPinR;

        //desired angular position of the servos
        int desPosL;
        int desPosR;

        //Servo freqeuncies
        int servoFreqLow; //500 for the Pololu servo
        int servoFreqHigh; //2500 for the Pololu servo
        
        void driveMotors(int desPosL, int desPosR);
};

#endif