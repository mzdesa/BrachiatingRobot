#ifndef Motors_H
#define Motors_H

#include <Arduino.h> //required to access the arduino functions.
#include <ESP32Servo.h> //Servo library
#include <ESP32Encoder.h> //encoder library

/*
This file contains the utilities for driving all motors.
*/
class Motors {
    public:
        Motors(); //default constructor
        Motors(int servo_pin_L, int servo_pin_R, int m_pin_1_L, int m_pin_2_L, int m_pin_1_R, int m_pin_2_R, int enc1_L, int enc2_L, int enc1_R, int enc2_R);
        void setDesPos(int des_pos_servo_L, int des_pos_servo_R, int des_pos_motor_L, int des_pos_motor_R);
        void driveDes();
        int getAngleMotorLeft();
        int getAngleMotorRight();
        void driveServos(int desPosL, int desPosR);
        void driveDCL(int des_pos);
        void driveDCR(int des_pos);
        void driveOLTest();
        void dcControllerTest();
    private:
        //Servo motors
        Servo servoL;
        Servo servoR;

        //DC Motor pins
        Servo motorL1;
        Servo motorL2;
        Servo motorR1;
        Servo motorR2;

        //PWM pins for the servos
        int servoPinL;
        int servoPinR;

        //PMW pins for the DC motors
        int mPin1L;
        int mPin2L;
        int mPin1R;
        int mPin2R;

        //Encoder pins for DC motors
        int encPin1L;
        int encPin2L;
        int encPin1R;
        int encPin2R;

        //Encoder object
        ESP32Encoder encoderL;
        ESP32Encoder encoderR;

        //motor parameters
        int MAX_PWM;
        int MIN_PWM;

        //controller paramters
        double Kp = 1;

        //desired angular position of the servos
        int desPosServoL;
        int desPosServoR;

        //desired angular position of the motors
        int desPosMotorL;
        int desPosMotorR;

        //Servo freqeuncies
        int servoFreqLow; //500 for the Pololu servo
        int servoFreqHigh; //2500 for the Pololu servo
};

#endif