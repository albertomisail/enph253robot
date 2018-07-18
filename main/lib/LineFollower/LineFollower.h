#pragma once
#include <Arduino.h>
#include <MotorBase.h>

class LineFollower
{
private:
    int32_t lastTime = 0;
    int16_t previousError = 0,
            deltaT = 0,
            previousTime = 0;
    uint8_t consec = 0;
    int16_t counter = 0;
    int16_t lastG = 0;
    bool movingState = false;

public:
    int32_t sensorLeftReading, sensorRightReading, sensorEdgeReading, g;
    int16_t error;
    void init();
    void start();
    void stop();
    bool poll();
    bool isMoving() const;
};

extern LineFollower lineFollower;
