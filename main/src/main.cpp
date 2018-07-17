#include <Arduino.h>
#include <EEPROM.h>
#include <OLED_I2C.h>
//#include "Constants.h"
//#include <FFT.h>
#include <Menu.h>
//#include <InfraredBase.h>
//#include <EncoderBase.h>
//#include <Encoder.h>
#include <ClawBase.h>
#include <UltrasoundBase.h>
//#include <ZiplineLiftBase.h>
#include "testAll.h"

extern uint8_t SmallFont[];

void setup() {
    //fft.init();
    Constants::init();
    oled.begin();
    oled.setFont(SmallFont);
    // put your setup code here, to run once:
    // ultrasound.init();
    claw.init();
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    // put your main code here, to run repeatedly:
    //oled.print("HI-", 0, 0);
    //oled.update();
    //delay(200);
    //testUltrasound();
    /*
    for(int i=0;i<5;++i)
    {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
        digitalWrite(LED_BUILTIN, LOW);
        delay(400);
    }*/

/*
    oled.clrScr();
    oled.print("HI", 0, 0);
    oled.update();
    delay(1000); */
    //testEncoder();
    //delay(15000);
    /*
    testClawOnly();
    oled.print("..", 0, 0);
    oled.update();
    delay(1000);
    oled.clrScr();
    oled.update();
    delay(1000); */
    testMenu();
}
