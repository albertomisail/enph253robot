#pragma once
#include <Arduino.h>

/**
 * TODO: Move these motor pin listings into constants.h
 *
 */

constexpr int8_t highPwmPins[] = {PA0};
constexpr int8_t lowPwmPins[] = {PA1};

static_assert(sizeof highPwmPins == sizeof lowPwmPins);

class MotorBase {
private:
    //int16_t speeds[sizeof highPwmPins];

public:
    MotorBase();
    constexpr static int8_t size();
    static void speed(const int8_t&);
    static void stop(const int8_t&);
    static void speed(const int8_t&, const int16_t&);
};
