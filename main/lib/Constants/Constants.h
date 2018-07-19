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
    static MenuItem EDGE_THRESHOLD;//("RT", 0, 4096, 1024);

    static void init();

    constexpr static uint8_t POT_PIN = PA0;
    constexpr static uint8_t GO_BTN_PIN = PB13;

    constexpr static int8_t oledPins[] = {PB7, PB10};

    constexpr static int8_t trigPins[] = {PB12}; constexpr static int8_t echoPins[] = {PB13};

    constexpr static int8_t highPwmPins[] = {PB8, PB0};
    constexpr static int8_t lowPwmPins[] = {PB9, PB1};

    constexpr static int16_t ENCODER_POLL_TIME = 2; // milliseconds

    // TODO: Assign real pin values
    constexpr static int8_t infraredLeds[] = {PB13};
    constexpr static int8_t infraredReceiver = PB13;
    constexpr static int16_t infraredThreshold = 10;

    constexpr static int8_t CLAW_ARM_PIN = PA6;
    constexpr static int8_t CLAW_PIN = PA7;
    constexpr static int16_t angleOut = 45;
    constexpr static int16_t angleIn = 0;
    constexpr static int16_t angleOpen = 20;
    constexpr static int16_t angleClose = 150;
    constexpr static int8_t buttonSwitchPin = PB13;

    constexpr static uint8_t IR_BEACON_PIN = PA0;

    constexpr static uint8_t clawLift = PB13;
    constexpr static uint8_t otherLift = PB13;
    constexpr static uint8_t potentiometerClaw = PB13;
    constexpr static uint8_t potentiometerOther = PB13;
    constexpr static uint8_t voltageUp = PB13;
    constexpr static uint8_t voltageDown = PB13;
    constexpr static uint8_t speedLift = PB13;

    constexpr static uint8_t LEFT_QRD_PIN = PA4;
    constexpr static uint8_t RIGHT_QRD_PIN = PA5;
    constexpr static uint8_t EDGE_QRD_PIN = PA2;
    constexpr static uint8_t QRD_POWER_PIN = PB4;

    constexpr static uint8_t MOTOR_LEFT = 0;
    constexpr static uint8_t MOTOR_RIGHT = 1;
    constexpr static int16_t LINE_FOLLOW_POLL_TIME = 5; // millis
};
