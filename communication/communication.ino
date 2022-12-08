#include "Electromagnet.h"

/*
 * This file currently contains unit tests for the arduino libraries written.
 */

int sPin = 13;
Electromagnet eMag(sPin);

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println("hi");
}
