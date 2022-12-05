#include <Arduino.h> //required to access the arduino functions.
#include <ESP32Encoder.h>
/*
This file contains utilities for driving a DC motor with an encoder.
*/
class DCMotor {
    public:
        DCMotor(int mp_1, int mp_2, int enc_1, int enc_2, int pwmCh1, int pwmCh2);
        void setDesPos();
        void driveDes();
        double getAngle();

    private:
        //class attributes
        int mp1; //motor pin 1
        int mp2; //motor pin 2
        int enc1; //encoder pin 1
        int enc2; //encoder pin 2

        //motor parameters
        const int MAX_PWM = 255;
        const int MIN_PWM = 0;
        const int freq = 5000;
        int pwmChannel1; //DEFAULT values are 1 and 2.
        int pwmChannel2;
        const int resolution = 8;
        const double counts2rad = 3; //conversion factor between encoder counts & rad
        const double rad2counts = 3; //conversion factor between rad & encoder counts
        ESP32Encoder encoder;

        //controller paramters
        double Kp = 1;
        int desPos = 3.14/3; //desired position in radians
        void driveMotor(double des_pos);
}