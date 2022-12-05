#include <Arduino.h> //required to access the arduino functions.
#include <ESP32Servo.h> //Servo library
/*
This file contains the utilities for driving BOTH servo motors.
*/
class ServoMotors {
    public:
        ServoMotors(int servo_pin);
        void setDesPos(double des_pos_1, double des_pos_2);
        void driveDes();
        void resetTimers();
        double getDesAngle1();
        double getDesAngle2();
    private:
        //Define esp32Servo objects
        Servo servo1;
        Servo servo2;

        //PWM pins for the servos
        int servoPin1;
        int servoPin2;

        //desired angular position of the servos
        int desPos1;
        int desPos2;

        //Servo freqeuncies
        const int servoFreqLow = 500; //500 for the Pololu servo
        const int servoFreqHigh = 2500; //2500 for the Pololu servo
        
        void driveMotors(int desPos1, int desPos2);
}