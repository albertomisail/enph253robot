#pragma once

#include <Arduino.h>
#include <MotorBase.h>
#include <Encoder.h>

class Movement {
private:
    bool moveState;
    int8_t leftDir, rightDir, leftAmt, rightAmt;
    Encoder leftEnc, rightEnc;
    int16_t leftInit, rightInit;

public:
    int32_t previousTime,
            deltaT,
            error,
            previousError,
            counter;

    Movement();
    void init();
    void start(int8_t leftDir_, int8_t rightDir_, int16_t leftAmt_, int16_t rightAmt_);
    void stop();
    bool isMoving() const;
    bool poll();
    bool oneSideFinished(int16_t, int16_t);

};
