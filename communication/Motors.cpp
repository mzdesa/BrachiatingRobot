#include "Motors.h"

/*
This file contains an implementation of the motors class.
*/

/*
Init function for a motor class
*/
Motors::Motors() {
    Motors(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
}
Motors::Motors(int servo_pin_L, int servo_pin_R, int m_pin_1_L, int m_pin_2_L, int m_pin_1_R, int m_pin_2_R, int enc1_L, int enc2_L, int enc1_R, int enc2_R){
    //define the servo pins
    servoPinL = servo_pin_L;
    servoPinR = servo_pin_R;

    //define the motor pins
    mPin1L = m_pin_1_L;
    mPin2L = m_pin_2_L;
    mPin1R = m_pin_1_R;
    mPin2R = m_pin_2_R;

    //define the encoder pins
    encPin1L = enc1_L;
    encPin2L = enc2_L;
    encPin1R = enc1_R;
    encPin2R = enc2_R;

    //set the pin modes to OUTPUT
    pinMode(servoPinL, OUTPUT);
    pinMode(servoPinR, OUTPUT);
    pinMode(mPin1L, OUTPUT);
    pinMode(mPin2L, OUTPUT);
    pinMode(mPin1R, OUTPUT);
    pinMode(mPin2R, OUTPUT);

    //set the encoder pins to INPUT
    pinMode(encPin1L, INPUT);
    pinMode(encPin2L, INPUT);
    pinMode(encPin1R, INPUT);
    pinMode(encPin2R, INPUT);

    //set up encoders
    ESP32Encoder::useInternalWeakPullResistors = UP; //Enable weak pullups
    encoderL.attachHalfQuad(encPin1L, encPin2L);
    encoderL.setCount(0); //INITIALIZE the encoder count to be zero!!
    encoderR.attachHalfQuad(encPin1R, encPin2R);
    encoderR.setCount(0); //INITIALIZE the encoder count to be zero!!

    //set the default desired servo positions, 60 degrees (vertical) - 41 degrees is a bar starting position.
    desPosServoL = 60;
    desPosServoR = 60;

    //set default desired motor positions
    desPosMotorL = 0;
    desPosMotorR = 0;

    //define frequencies
    servoFreqLow = 500; //500 for the Pololu servo
    servoFreqHigh = 2500; //2500 for the Pololu servo

    //define PWM constants
    MAX_PWM = 180;
    MIN_PWM = 0;

    //define controller constants
    Kp = 1;
    
    //allocate the timers
    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);   

    //set the servo periods
    servoL.setPeriodHertz(50); 
    servoR.setPeriodHertz(50);

    //set the motor pin periods
    motorL1.setPeriodHertz(50); 
    motorL2.setPeriodHertz(50);
    motorR1.setPeriodHertz(50); 
    motorR2.setPeriodHertz(50);

    //attach the servos to their PWM pins
    servoL.attach(servoPinL, servoFreqLow, servoFreqHigh);
    servoR.attach(servoPinR, servoFreqLow, servoFreqHigh);

    //attach the motors pwm pins
    motorL1.attach(mPin1L, servoFreqLow, servoFreqHigh);
    motorL2.attach(mPin2L, servoFreqLow, servoFreqHigh);
    motorR1.attach(mPin1R, servoFreqLow, servoFreqHigh);
    motorR2.attach(mPin2R, servoFreqLow, servoFreqHigh);

    //drive the servos to their initial position!
    int startPos = 41; //option to begin it in the start position with one fwd one back.
    servoL.write(startPos); //writes it NOT to the vertical but to 60
    servoR.write(startPos);
}

/*
Function to set the desired positions of the two servo motors.
Inputs:
    des_pos_1 (int) : desired position in radians of the first servo
    des_pos_2 (int) : desired position in radians of the second servo
*/
void Motors::setDesPos(int des_pos_servo_L, int des_pos_servo_R, int des_pos_motor_L, int des_pos_motor_R) {
    desPosServoL = des_pos_servo_L;
    desPosServoR = des_pos_servo_R;
    desPosMotorL = des_pos_motor_L;
    desPosMotorR = des_pos_motor_R;
}

/*
Function to drive the servo motors to the desired position stored in the class
*/
void Motors::driveDes() {
    driveServos(desPosServoL, desPosServoR);
    driveDCL(desPosMotorL);
    driveDCR(desPosMotorR);
}

/*
Function to drive the two servo motors
Inputs:
    desPos1 (int) : desired position from 0 to 180 of the first servo
    desPos2 (int) : desired position from 0 to 180 of the second servo
*/
void Motors::driveServos(int desPosL, int desPosR) {
    //drive the first servo motor to desPos1
    servoL.write(desPosL);
    //derive the second servo motor to desPos2
    servoR.write(desPosR);
    return;
}

/*
Function to return the current angle of the DC motor, as read by the encoder in ticks.
Returns:
    motorAngle (int) : positional reading of the encoder in encoder units
*/
int Motors::getAngleMotorLeft() {
    return (int32_t)encoderL.getCount();
}

int Motors::getAngleMotorRight() {
    return (int32_t)encoderR.getCount();
}

/*
Function to drive the DC motor to the correct position using FB control
The right arm has a negative feedback gain as it is flipped.
Inputs:
    des_pos (double) : desired position in radians. NOT the class attribute
*/
void Motors::driveDCL(int des_pos) {
    //next, calculate the control input
    int controlInput = floor(Kp*(des_pos - (int32_t)encoderL.getCount()));

    //drive the motor with a PWM according to the control input
    if (controlInput >= 0) {
        //clamp the control input
        controlInput = min(MAX_PWM, max(MIN_PWM, controlInput));

        //write one pin high, the other low
        motorL1.write(controlInput);
        digitalWrite(mPin2L, LOW);
        // motorL2.write(0);
    } else {
        //flip the sign of the control input
        controlInput = -1*controlInput;

        //clamp the control input
        controlInput = min(MAX_PWM, max(MIN_PWM, controlInput));

        //drive the motor
        // motorL1.write(0);
        digitalWrite(mPin1L, LOW);
        motorL2.write(controlInput);
    }
}

void Motors::driveDCR(int des_pos) {
    //next, calculate the control input SWITCHING the sign of Kp to (-)
    int controlInput = floor(-Kp*(des_pos - (int32_t)encoderR.getCount()));

    //drive the motor with a PWM according to the control input
    if (controlInput >= 0) {
        //clamp the control input
        controlInput = min(MAX_PWM, max(MIN_PWM, controlInput));

        Serial.println(controlInput);

        //write one pin high, the other low
        motorR1.write(controlInput);
        // motorR2.write(0);
        digitalWrite(mPin2R, LOW);
    } else {
        //flip the sign of the control input
        controlInput = -1*controlInput;

        //clamp the control input
        controlInput = min(MAX_PWM, max(MIN_PWM, controlInput));

        Serial.println(controlInput);

        //drive the motor
        // motorR1.write(0);
        digitalWrite(mPin1R, LOW);
        motorR2.write(controlInput);
    }
}

void Motors::driveOLTest() {
    // motorR1.write(0);
    digitalWrite(mPin2R, LOW);
    motorR1.write(180);
}

void Motors::dcControllerTest() {
    //give the controller a small setpoint that it must reach.Assume it starts at zero.
    int setpt = 300;
    driveDCR(setpt);
}