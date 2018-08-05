#include <Arduino.h>
#include <EEPROM.h>
#include <OLED_I2C.h>
#include "Constants.h"
#include <Menu.h>
#include <ClawBase.h>
#include <MotorBase.h>
#include <Movement.h>
#include "testAll.h"
#include <procedures.h>

extern uint8_t SmallFont[];

void setup() {
    Serial.begin(9600);
    delay(1000);
    Constants::init();
    oled.begin();
    oled.setFont(SmallFont);
    lineFollower.init(0);
    motor.init();
    infrared.init();
    claw.init();
    pinMode(PB5, OUTPUT);
}

void loop() {
    digitalWrite(PB5, HIGH);
    delay(1000);
    motor.speed(Constants::MOTOR_LEFT, 100);
    motor.speed(Constants::MOTOR_RIGHT, 100);
    delay(1000);
    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0);
    delay(20);
    motor.speed(Constants::MOTOR_LEFT, -100);
    motor.speed(Constants::MOTOR_RIGHT, -100);
    delay(1000);
    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0);
    delay(5000);
    //mainRun();
    //delay(10000);
}