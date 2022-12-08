#ifndef DCMotor_H
#define DCMotor_H

#include <Arduino.h> //required to access the arduino functions.
#include <ESP32Encoder.h>
/*
This file contains utilities for driving a DC motor with an encoder.
*/
class DCMotor {
    public:
        DCMotor(); //default constructor
        DCMotor(int mp_1, int mp_2, int enc_1, int enc_2, int pwmCh1, int pwmCh2);
        void setDesPos(int des_pos);
        void driveDes();
        int getAngle();

    private:
        //class attributes
        int mp1; //motor pin 1
        int mp2; //motor pin 2
        int enc1; //encoder pin 1
        int enc2; //encoder pin 2

        //motor parameters
        int MAX_PWM;
        int MIN_PWM;
        int freq;
        int pwmChannel1; //DEFAULT values are 1 and 2.
        int pwmChannel2;
        int resolution;
        double counts2rad; //conversion factor between encoder counts & rad
        double rad2counts; //conversion factor between rad & encoder counts
        ESP32Encoder encoder;

        //controller paramters
        double Kp = 1;
        int desPos = 0; //desired position in radians
        void driveMotor(double des_pos);
};

#endif
