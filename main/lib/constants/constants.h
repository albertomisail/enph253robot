#pragma once
#include <Arduino.h>

constexpr int8_t lowPwmPins[] = {PA0};
constexpr int8_t highPwmPins[] = {PA1};

static_assert(sizeof lowPwmPins == sizeof highPwmPins);
