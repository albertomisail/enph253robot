#pragma once
#include <Arduino.h>
#include <Constants.h>

class MotorBase {
private:
    int16_t speeds[sizeof highPwmPins];

public:
    MotorBase();
    constexpr static int8_t size();
    void init();
    void speed(const int8_t&, int16_t);
    void stop(const int8_t&);
    void shut_down();
};

extern MotorBase motor;