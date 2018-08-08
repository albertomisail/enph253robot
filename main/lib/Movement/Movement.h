#pragma once

#include <Arduino.h>
#include <MotorBase.h>
#include <Encoder.h>
#include <OLED_I2C.h>

struct MovementInstruction {
    int8_t leftDir;
    int8_t rightDir;
    int16_t leftAmt;
    int16_t rightAmt;
    int16_t correctionSpeed;
};

class Movement {
private:
    bool moveState = false;
    int16_t leftDir = 0, rightDir = 0, leftAmt = 0, rightAmt = 0;
    Encoder leftEnc, rightEnc;
    int16_t leftInit = 0, rightInit = 0;
    int16_t correctionSpeed = 0;

public:
    int32_t previousTime = 0,
            deltaT = 0,
            error = 0,
            previousError = 0,
            counter, cnt = 0;

    Movement();
    void init();
    void start(int8_t, int8_t, int16_t, int16_t, int16_t);
    void start(MovementInstruction);
    void stop();
    bool isMoving() const;
    bool poll();
    bool oneSideFinished(int16_t, int16_t);
    void move(int8_t, int8_t, int16_t, int16_t, int16_t);
    void move(MovementInstruction);
    MovementInstruction reverseLast();

};
