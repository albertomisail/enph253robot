#pragma once
#include <MenuItem.h>

class Constants {
public:
    static MenuItem PROPORTIONAL;//("P", 0, 256, 40);
    static MenuItem INTEGRAL;//("I", 0, 20, 0);
    static MenuItem DERIVATIVE;//("D", 0, 40, 5);
    static MenuItem BASE_SPEED;//("BS", 0, 256, 150);
    static MenuItem LEFT_THRESHOLD;//("LT", 0, 4096, 1024);
    static MenuItem RIGHT_THRESHOLD;//("RT", 0, 4096, 1024);

    constexpr static uint8_t POT_PIN = PB0;
    constexpr static uint8_t GO_BTN_PIN = PB12;

    constexpr static int8_t oledPins[] = {PB7, PB6};

    constexpr static int8_t trigPins[] = {PB12};
    constexpr static int8_t echoPins[] = {PB13};

    constexpr static int8_t highPwmPins[] = {PB8, PA6};
    constexpr static int8_t lowPwmPins[] = {PB9, PA7};

    constexpr static int8_t leftEncoderPins[] = {};
    constexpr static int8_t rightEncoderPins[] = {};

    // TODO: Assign real pin values
    constexpr static int8_t infraredLeds[] = {PB13};
    constexpr static int8_t infraredReceiver = PB13;
    constexpr static int16_t infraredThreshold = 10;

    constexpr static int8_t clawArm = PB13;
    constexpr static int8_t claw = PB13;
    constexpr static int8_t angleOut = PB13;
    constexpr static int8_t angleIn = PB13;
    constexpr static int8_t angleOpen = PB13;
    constexpr static int8_t angleClose = PB13;
    constexpr static int8_t buttonSwitchPin = PB13;

    constexpr static uint8_t IR_BEACON_PIN = PA0;

    constexpr static uint8_t clawLift = PB13;
    constexpr static uint8_t otherLift = PB13;
    constexpr static uint8_t potentiometerClaw = PB13;
    constexpr static uint8_t potentiometerOther = PB13;
    constexpr static uint8_t voltageUp = PB13;
    constexpr static uint8_t voltageDown = PB13;
    constexpr static uint8_t speedLift = PB13;
};
