#include "Communication.h"
/*
This file contains an implementation of the Communication class
*/

//Initialization function
Communication::Communication(int rle, int p0, int p1, int p2, int p3) {
    //Assign role and pin numbers
    role = rle;
    pin0 = p0;
    pin1 = p1;
    pin2 = p2;
    pin3 = p3;
    commPins = {pin0, pin1, pin2, pin3};

    //Depending on the role, assign pins as input or output
    if (role == 0) {
        //assign pins as input, as the child board reads the pins
        for (int i = 0; i < numPins; i++) {
        pinMode(commPins[i], INPUT);
        }
    } else {
        //assign pins as output, as the parent board sends the information
        for (int i = 0; i < numPins; i++) {
        pinMode(commPins[i], OUTPUT);
        }
    }
}

/*
Encoding function to encode an integer message labeled input.
The input message should be bounded above by 2^numPins and below by 0
Inputs:
n (int) : number to be encoded into binary (e.g. 13)
Returns:
binNum (int) : number written in binary (e.g. 1101)
*/
Communication::binaryEncode(int n) {
    //clamp the integer n between 0 and 2^numPins - 1
    n = min(pow(2, numPins), n);
    n = max(n, 0);
    //Convert the message n to a binary number - arduino floors divides ints
    int binNum; //declare a binary number
    int i = numPins - 1;
    while (n / 2 > 0) {
        binNum = binNum + pow(10, i)*(n%2); //represent the binary number using decimal notation
        n = n/2;
        i--;
    }
    return binNum;
}

/*
Decoding function to decode a binary integer message into a decimal.
Inputs:
b (int) : 4 digit binary number to be decoded
Returns:
decimalNum (int) : decimal representation of b, between 0 and 2^numPins
*/
Communication::binaryDecode(int b) {
    //decode a binary number b into decimal
    int decimalNum = 0;
    int i = 0; //incremental variable
    while (b > 0) {
        decimalNum = decimalNum + pow(10, i) * b % 10;
        b = b/10;
        i++; 
    }
} 

/*
Function to send an integer signal n (NOT encoded) across the pins.
This function is ONLY to be used by the parent board.
Inputs:
n (int): number between 0 and 2^numPins to be sent across the boards
*/
Communication::sendSignal(int n) {
    //convert the input signal to binary
    int binNum = binaryEncode(n);

    //send each digit to each of the pin in the commPins
    for (int i = 0; i < numPins; i++) {
        //extract one of the binary digits
        int b = binNum % 10; //will be a 1 or 0 (High or Low)
        digitalWrite(commPins[i], b);
        //floor divide b by 10
        b = b/10;
    }
}

/*
Function to read the signal at the communication pins.
This function is ONLY to be used by the child board.
Returns:
n: decoded integer signal between 0 and 2^numPins.
*/
Communication::readSignal() {
    //loop over the input pins and generate a binary number to be decoded
    int binNum = 0;
    for (int i = 0; i<numPins; i++) {
        binNum = binNum + pow(10, i)*digitalRead(commPins[i]);
    }
    //decode this binary number into an integer & return it
    return binaryDecode(binNum);
}