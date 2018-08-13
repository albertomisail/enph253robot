#pragma once
#include <Arduino.h>
#include <Constants.h>

class InfraredBase {
private:
    int lastResult = 0;
    bool started = false, isMeasuring = false;
    int32_t startTime = true;
    int32_t nextAvailable = 0;
    int16_t base;

public:
    InfraredBase();
    constexpr static int8_t size();
    void init();
    void performStartMeasurement();
    void startMeasurement();
    bool isDone() const;
    bool poll();
    int lastMeasurement() const;
    bool objectDetected(int16_t infraredThreshold);
};

extern InfraredBase infrared;
