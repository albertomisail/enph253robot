#pragma once
#include <Arduino.h>

constexpr int8_t highPwmPins[] = {PB8, PA6};
constexpr int8_t lowPwmPins[] = {PB9, PA7};

static_assert(sizeof lowPwmPins == sizeof highPwmPins);