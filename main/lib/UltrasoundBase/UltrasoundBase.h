#pragma once
#include <hcsr04.h>
// https://github.com/bbkbarbar/Arduino-HC-SR04-library/blob/master/hcsr04.h
// If it does not work try https://playground.arduino.cc/Code/NewPing
#include <Arduino.h>
#include <Constants.h>

class UltrasoundBase {
private:
    HCSR04 sensors[sizeof Constants::trigPins];
    float distances[sizeof Constants::trigPins];

public:
    UltrasoundBase();
    constexpr static int8_t size();
    void init();
    unsigned short measureDistance(const int8_t&);
};

extern UltrasoundBase ultrasound;
