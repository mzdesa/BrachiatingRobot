#include <ESP32Encoder.h>
/*
This file contains utilities for driving a DC motor with an encoder.
*/
class DCMotor {
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
    ESP32Encoder encoder;

    //controller paramters
    double Kp = 1;
    int desPos = 3.14/3; //desired position in radians

    /*
    Constructor for a motor pin object.
    Inputs:
        mP1 (int) : first motor pin
        mP2 (int) : second motor pin
        enc_1 (int) : first encoder pin
        enc_2 (int) : second encoder pin
        pwmCh1 (int) : first PWM channel (default should be 1 or 3)
        pwmCh2 (int) : second PWM channel (default should be 2 or 4)
    */
    DCMotor(int mp_1, int mp_2, int enc_1, int enc_2, int pwmCh1, int pwmCh2) {
        //assign motor pins
        mp1 = mp_1;
        mp2 = mp_2;

        //assign encoder pins
        enc1 = enc_1;
        enc2 = enc_2;

        //assign PWM channels
        pwmChannel1 = pwmCh1;
        pwmChannel2 = pwmCh2;

        //set up encoder
        ESP32Encoder::useInternalWeakPullResistors = UP; //Enable weak pullups
        encoder.attachHalfQuad(enc1, enc2);
        encoder.setCount(0); //INITIALIZE the encoder count to be zero!!
        
        //set up pin modes for the motor pins
        pinMode(mp1, OUTPUT);
        pinMode(mp2, OUTPUT);

        //set up PWM functionality on the PWM channels
        ledcSetup(pwmChannel1, freq, resolution);
        ledcSetup(pwmChannel2, freq, resolution);

        //attach the channel to the GPIO motor pins
        ledcAttachPin(mp1, pwmChannel1);
        ledcAttachPin(mp2, pwmChannel2);
    }

    /*
    Function to drive the DC motor to the correct position using FB control
    Inputs:
        desPos (double) : desired position in radians.
    */
   void driveMotor(double desPos) {
        //First, convert the desired position into encoder counts
        desPos = counts2rad*desPos;

        //next, calculate the control input
        int controlInput = floor(Kp*(desPos - (int32_t)encoder.getCount()));

        //drive the motor with a PWM according to the control input
        if (controlInput >= 0) {
            //clamp the control input
            controlInput = min(MAX_PWM, max(MIN_PWM, controlInput));

            //write one pin high, the other low
            ledcWrite(pwmChannel1, controlInput);
            ledcWrite(pwmChannel2, LOW);
        } else {
            //flip the sign of the control input
            controlInput = -1*controlInput;

            //clamp the control input
            controlInput = min(MAX_PWM, max(MIN_PWM, controlInput));

            //drive the motor
            ledcWrite(pwmChannel1, LOW);
            ledcWrite(pwmChannel2, controlInput);
        }
   }
}