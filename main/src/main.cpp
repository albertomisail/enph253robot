#include <Arduino.h>
#include <EEPROM.h>
#include <OLED_I2C.h>
//#include "Constants.h"
//#include <FFT.h>
//#include <Menu.h>
//#include <InfraredBase.h>
//#include <EncoderBase.h>
//#include <Encoder.h>
//#include <ClawBase.h>
#include <UltrasoundBase.h>
//#include <ZiplineLiftBase.h>
#include "testAll.h"

extern uint8_t SmallFont[];

void setup() {
    //fft.init();
    oled.begin();
    oled.setFont(SmallFont);
    // put your setup code here, to run once:
    ultrasound.init();
}

void loop() {
    // put your main code here, to run repeatedly:
    //oled.print("HI-", 0, 0);
    //oled.update();
    //delay(200);
    //testUltrasound();
    testEncoder();
}
