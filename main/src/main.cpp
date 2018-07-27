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
    oled.begin();
    oled.setFont(SmallFont);
    Constants::init();
    lineFollower.init(0);
    motor.init();
    ziplineLift.init();
    infrared.init();
    pinMode(PA8, OUTPUT);
    digitalWrite(PA8,LOW);
    claw.init();
}

void loop() {
    mainRun();
    //testLFandReverse();
}
