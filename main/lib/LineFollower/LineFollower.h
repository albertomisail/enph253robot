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

    bool isQRDReading = false, hasQRDStarted = false;

public:
    int32_t sensorLeftReading, sensorRightReading, sensorEdgeReading, g;
    int32_t sensorLeftReadingAmb, sensorRightReadingAmb, sensorEdgeReadingAmb;
    int32_t sensorLeftReadingPow, sensorRightReadingPow, sensorEdgeReadingPow;
    int32_t edgeStopThreshold, leftStopThreshold, rightStopThreshold;
    int16_t error;
    int32_t lastCompTime;

    int32_t nextAvailableQRDTime=0;
    //constexpr static int8_t infraredReceiver = PA5;

    constexpr static int8_t DIR_LEFT = 0;
    constexpr static int8_t DIR_RIGHT = 0; // TODO assign useful values of left, right

    void startQRD();
    bool QRDPoll();
    bool QRDIsReading() const;
    void QRDGetInitialReading();
    int16_t QRDMeasurement(char c) const;

    void init(int);
    void start();
    void start(int ,int, int);
    void stop();
    bool poll();
    bool isMoving() const;

    void findLine(const int8_t&);
};

extern LineFollower lineFollower;
