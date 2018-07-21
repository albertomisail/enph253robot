#pragma once
#include <Arduino.h>
#include <MotorBase.h>

class LineFollower
{
private:
    int32_t lastTime = 0;
    int16_t previousError = 0;
    int32_t deltaT = 0,
            previousTime = 0;
    uint8_t consec = 0;
    int16_t counter = 0;
    int16_t lastG = 0;
    uint8_t state = 0;
    bool movingState = false;

public:
    int32_t sensorLeftReading, sensorRightReading, sensorEdgeReading, g;
    int32_t sensorLeftReadingAmb, sensorRightReadingAmb, sensorEdgeReadingAmb;
    int32_t sensorLeftReadingPow, sensorRightReadingPow, sensorEdgeReadingPow;
    int16_t error, lastCompTime;
    void init();
    void start();
    void stop();
    bool poll();
    bool isMoving() const;
};

extern LineFollower lineFollower;
