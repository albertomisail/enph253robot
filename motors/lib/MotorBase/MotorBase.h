#pragma once
#include <Arduino.h>
#include <MyOLED.h>

/**
 * TODO: Move these motor pin listings into constants.h
 *
 */

constexpr int8_t highPwmPins[] = {PB8, PA6};
constexpr int8_t lowPwmPins[] = {PB9, PA7};

static_assert(sizeof highPwmPins == sizeof lowPwmPins);

class MotorBase {
private:
    int16_t speeds[sizeof highPwmPins];

public:
    MotorBase();
    constexpr static int8_t size();
    void stop(const int8_t&);
    void init();
    void speed(const int8_t&, int16_t);
};

extern MotorBase motor;
