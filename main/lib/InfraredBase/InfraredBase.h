#pragma once
#include <Arduino.h>
#include <Constants.h>

class InfraredBase {
private:

public:
    InfraredBase();
    constexpr static int8_t size();
    void init();
    int makeMeasurement();
    bool objectDetected(int16_t infraredThreshold);
};

extern InfraredBase infrared;