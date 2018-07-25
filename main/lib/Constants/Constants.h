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

    constexpr static int16_t PROPORTIONAL_MOVEMENT = 20;
    constexpr static int16_t DERIVATIVE_MOVEMENT = 3;

    static void init();

    constexpr static uint8_t POT_PIN = PA1;
    constexpr static uint8_t GO_BTN_PIN = PB13;

    constexpr static int8_t oledPins[] = {PB11, PB10};

    constexpr static int8_t trigPins[] = {PB12}; constexpr static int8_t echoPins[] = {PB13};

    constexpr static int8_t highPwmPins[] = {PB8, PB0, PB6};
    constexpr static int8_t lowPwmPins[] = {PB9, PB1, PB7};

    constexpr static int16_t ENCODER_POLL_TIME = 2; // milliseconds

    // TODO: Assign real pin values
    constexpr static int8_t infraredLeds[] = {PB3};
    constexpr static int8_t infraredReceiver = PA5;
    constexpr static int16_t pickUpInfraredThreshold = 1900;
    constexpr static int16_t distantInfaredThreshold = 1200;
    constexpr static int8_t CLAW_ARM_PIN = PA6;
    constexpr static int8_t CLAW_PIN = PA7;
    constexpr static int16_t angleOut = 0;
    constexpr static int16_t angleInit = 40;
    constexpr static int16_t angleIn = 45;
    constexpr static int16_t angleOpen = 0;
    constexpr static int16_t angleClose = 80;
    //constexpr static int16_t angleFullClose = 20;
    constexpr static int8_t buttonSwitchPin = PA15;

    constexpr static uint8_t IR_BEACON_PIN = PA5;

    //constexpr static uint8_t LIFT_MOTOR = 1;
    constexpr static uint8_t frontLift = 1;
    constexpr static uint8_t backLift = PB13;
    constexpr static uint8_t potFront = PA0;
    constexpr static uint8_t potBack = PB13;
    constexpr static uint16_t voltageUpFront = 800;
    constexpr static uint16_t voltageDownFront = 1170;
    constexpr static uint16_t voltageUpBack = 1050;
    constexpr static uint16_t voltageDownBack = 850;
    constexpr static uint8_t speedLiftDown = 100;
    constexpr static uint8_t speedLiftUp = 150;

    constexpr static uint8_t LEFT_QRD_PIN = PA4;
    constexpr static uint8_t RIGHT_QRD_PIN = PA3;
    constexpr static uint8_t EDGE_QRD_PIN = PA2;
    constexpr static uint8_t QRD_POWER_PIN = PB4;

    constexpr static uint8_t MOTOR_LEFT = 0;
    constexpr static uint8_t MOTOR_RIGHT = 1;
    constexpr static int16_t LINE_FOLLOW_POLL_TIME = 3; // millis

    // constexpr static int16_t CORRECTION_SPEED = 120;

    constexpr static uint8_t LEFT_ENC_PIN = PB14;
    constexpr static uint8_t RIGHT_ENC_PIN = PB15;
};
