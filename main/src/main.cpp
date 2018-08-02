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
    infrared.init();
    claw.init();
    pinMode(PB5, OUTPUT);
}

void loop() {
    /*
    int cnt = 0;
    digitalWrite(PB5, LOW);
    infrared.startMeasurement();
    while(true) {
        if(!infrared.poll()) {
            if((cnt++)%30 == 0) {
                oled.clrScr();
                oled.printNumI(infrared.lastMeasurement(), 0, 0);
                oled.update();
            }
            infrared.startMeasurement();
        }
    } */


    digitalWrite(PB5, HIGH);
    mainRun();
}
