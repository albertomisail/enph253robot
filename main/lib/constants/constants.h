#pragma once
#include <Arduino.h>
#include <EEPROM.h>
#include <MenuItem.h>

/**
 * NOTE: you will likely
 *
 */

class Constants {
private:
    int16_t vals[20];
public:
    static uint8_t lowPwmPins[2];
    static uint8_t highPwmPins[2];
    constexpr static MenuItem PROPORTIONAL = MenuItem("P", 0, 256, 40);
    constexpr static MenuItem INTEGRAL = MenuItem("I", 0, 20, 0);
    constexpr static MenuItem DERIVATIVE = MenuItem("D", 0, 40, 5);
    constexpr static MenuItem BASE_SPEED = MenuItem("BS", 0, 256, 150);
    constexpr static MenuItem LEFT_THRESHOLD = MenuItem("LT", 0, 4096, 1024);
    constexpr static MenuItem RIGHT_THRESHOLD = MenuItem("RT", 0, 4096, 1024);
    void load(int16_t addr);
    void dump(int16_t addr);
    constexpr static size_t size();
};
