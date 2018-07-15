#pragma once
#include <hcsr04.h>
#include <Arduino.h>

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