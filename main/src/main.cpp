#include <Arduino.h>
#include <EEPROM.h>
#include <OLED_I2C.h>
#include "Constants.h"
#include <Menu.h>
#include <ClawBase.h>
#include <UltrasoundBase.h>
#include <ZiplineLiftBase.h>
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
    //ziplineLift.init();
    //infrared.init();
    //claw.init();
    pinMode(PB5, OUTPUT);
}

void loop() {
    digitalWrite(PB5, HIGH);
    motor.speed(Constants::MOTOR_LEFT, 120);
    while(true){};
    // testLFandReverse();
    // delay(1000);
    // digitalWrite(LED_BUILTIN, HIGH);
    // delay(1000);
    // digitalWrite(LED_BUILTIN, LOW);
    // oled.clrScr();
    // oled.print("MOTOR SPEED", 0, 0);
    // Serial.println("!!");
    // oled.update();
    // motor.speed(Constants::MOTOR_LEFT, 130);
    // motor.speed(Constants::MOTOR_RIGHT, 130);
    // while(true){}

    /*
    Servo s;
    s.attach(PA8);
    while(true) {
        s.write(0);
        delay(1000);
        s.write(100);
        delay(1000);
    } */
    //mainRun();
    //testLFandReverse();
}
