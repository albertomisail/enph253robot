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
    // infrared.startMeasurement();
    // while(true) {
    //     if(!infrared.poll()) {
    //         oled.clrScr();
    //         oled.printNumI(infrared.lastMeasurement(), 0, 0);
    //         oled.update();
    //         infrared.startMeasurement();
    //     }
    // }
    pinMode(PB5, OUTPUT);

    digitalWrite(PB5, HIGH);
    delay(5000);
    
    mainRun();
    //delay(10000);
}
