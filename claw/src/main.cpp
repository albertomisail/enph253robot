#include "Arduino.h"

void setup() {
    Serial.begin(9600);
}

void loop() {
    analogWrite(PB6, 150);
    analogWrite(PB7, 0);
    analogWrite(PB8, 150);
    analogWrite(PB9, 0);
}
/*#include <Arduino.h>

void setup() {
    // put your setup code here, to run once:
}

void loop() {
    // put your main code here, to run repeatedly:
}*/
