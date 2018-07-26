#include <Arduino.h>
#include <EEPROM.h>
#include <OLED_I2C.h>
#include "Constants.h"
//#include <FFT.h>
#include <Menu.h>
//#include <InfraredBase.h>
//#include <EncoderBase.h>
//#include <Encoder.h>
#include <ClawBase.h>
#include <UltrasoundBase.h>
#include <ZiplineLiftBase.h>
#include "testAll.h"
#include <MotorBase.h>
#include <Movement.h>

extern uint8_t SmallFont[];

void setup() {
    Serial.begin(9600);
    delay(1000);
    oled.begin();
    oled.setFont(SmallFont);
    fft.init();
    Constants::init();
    //oled.begin();
    //oled.setFont(SmallFont);
    lineFollower.init(0);
    claw.init();
    motor.init();
    ziplineLift.init();
    infrared.init();
    pinMode(PA8, OUTPUT);
    digitalWrite(PA8,LOW);
    // put your setup code here, to run once:
    // ultrasound.init();
    //claw.init();
    //pinMode(LED_BUILTIN, OUTPUT);
    //pinMode(PB6, OUTPUT);
    //pinMode(PB7, OUTPUT);
    //pinMode(PA1, INPUT);
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
    //testMenu();
    //testLineFollow();
    //testLineFollow();
    //delay(1000);
    //testFFT();
    //oled.print("!!", 0, 0);
    //oled.update();
    //testEncoders();
<<<<<<< HEAD
    testLFandReverse();
=======
    // testLFandReverse();
>>>>>>> 24bf71711351fb88fd7656af6ede7ecdd14d5114
    //testPickingUpEwok();
    //delay(2000);
    //testLift();
    //testMovement();
    // crossBridge();
<<<<<<< HEAD
    //testInfrared();
=======
    // testInfrared();
    // encoderReadings();
    fftTuning();

    
/*
    int8_t TPIN = PA8;
    pinMode(TPIN, OUTPUT);

    while(true) {
        digitalWrite(TPIN, HIGH);
        delay(100);
        digitalWrite(TPIN, LOW);
        delay(100);
    }*/
>>>>>>> 24bf71711351fb88fd7656af6ede7ecdd14d5114
}
