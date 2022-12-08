#include <Arduino.h> //required to access the arduino functions.
/*
 * This file contains a class used for communication between two ESP32s.
 * It contains utilities for encoding and decoding different pieces of data
 * according to a binary communication protocol.
 * Structure:
 * Attribute: parent & child - one esp32 is marked as the sender, the other is the receiver
 * Assumes a four bit data communication structure.
 */
class Communication {
  private:
    //parent = 1, child = 0
    int role; 
    
    //declare communication pins
    int pin0; //represents '2^0' place in binary
    int pin1; //represents '2^1' place in binary
    int pin2; //represents '2^2' place in binary
    int pin3; //represents '2^3' place in binary

    //stores pins in a list
    int commPins[4];

    //declare number of communication pins
    int numPins = 4;
  
  public:
    Communication(int rle, int p0, int p1, int p2, int p3);
    int binaryEncode(int n);
    int binaryDecode(int b);
    void sendSignal(int n);
    int readSignal();
}; //NOTE: A semicolon is required at the end of a class.