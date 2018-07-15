#pragma once
#include <Arduino.h>
#include <Servo.h>
#include <Constants.h>

class ClawBase{
    private:
        Servo arm;
        Servo claw;
        bool buttonSwitch;
        bool bridge;

    public:
        ClawBase();
        void init();
}

class UltrasoundBase {
private:
    HCSR04 sensors[sizeof highPwmPins];
    float distances[sizeof highPwmPins];

public:
    UltrasoundBase();
    constexpr static int8_t size();
    void init();
    unsigned short measureDistance(const int8_t&);
};

extern UltrasoundBase ultrasound;