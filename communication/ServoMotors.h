#include <Arduino.h> //required to access the arduino functions.
#include <ESP32Servo.h> //Servo library
/*
This file contains the utilities for driving BOTH servo motors.
*/
class ServoMotors {
    public:
        ServoMotors(int servo_pin);
        void setDesPos(double des_pos_L, double des_pos_R);
        void driveDes();
        void resetTimers();
        int getDesAngleL();
        int getDesAngleR();
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
        const int servoFreqLow = 500; //500 for the Pololu servo
        const int servoFreqHigh = 2500; //2500 for the Pololu servo
        
        void driveMotors(int desPosL, int desPosR);
}