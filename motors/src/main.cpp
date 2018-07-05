#include <Arduino.h>
#include <MotorBase.h>

MotorBase motor;

void setup() {
}

void loop() {
    // put your main code here, to run repeatedly:
    for(int i=0;i<4;++i) {
        motor.speed(0, min(255, max(-255, i*256-512)));
        delay(500);
    }
}
