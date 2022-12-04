#include <ESP32Servo.h>
/*
This file contains the utilities for driving BOTH servo motors.
*/
class ServoMotors {
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

    public:
    /*
    Init function for a servo motor.
    Inputs:
        servoPin (int) : PWM pin used to control the servo motor
        allocate
    */
    ServoMotors(int servo_pin) {
        //define the servo pin
        servoPin = servo_pin;
        
        //allocate the timers
        ESP32PWM::allocateTimer(0);
        ESP32PWM::allocateTimer(1);
        ESP32PWM::allocateTimer(2);
        ESP32PWM::allocateTimer(3);   

        //set the servo periods
        servo1.setPeriodHertz(50); 
        servo2.setPeriodHertz(50);

        //attach the servos to their PWM pins
        servo1.attach(servoPin1, servoFreqLow, servoFreqHigh);
        servo2.attach(servoPin2, servoFreqLow, servoFreqHigh);
    }

    /*
    Function to drive the two servo motors
    Inputs:
        desPos1 (int) : desired position from 0 to 180 of the first servo
        desPos2 (int) : desired position from 0 to 180 of the second servo
    */
    void driveMotors(int desPos1, int desPos2) {
        //drive the first servo motor to desPos1
        servo1.write(desPos1);
        //derive the second servo motor to desPos2
        servo2.write(desPos2);
    }

    /*
    Function to reset the servo timers. To be used only if servo and DC
    are run on the same board.
    */
    void resetTimers() {
        //allocate the timers
        ESP32PWM::allocateTimer(0);
        ESP32PWM::allocateTimer(1);
        ESP32PWM::allocateTimer(2);
        ESP32PWM::allocateTimer(3);   

        //set the servo periods
        servo1.setPeriodHertz(50); 
        servo2.setPeriodHertz(50);
    }
}