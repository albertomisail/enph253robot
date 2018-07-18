#include "testAll.h"

void testUltrasound() {
    oled.clrScr();
    oled.print(const_cast<char*>("dist: "), 0, 0);
    //oled.printNumI(ultrasound.measureDistance(0), 35, 0);
    HCSR04 hcsr;
    hcsr.init(Constants::trigPins[0], Constants::echoPins[0]);
    long disc = hcsr.readDisctanceInMm();
    oled.printNumI(disc, 35, 0);
    oled.update();
    delay(200);
}

void testEncoder() {
    Encoder enc(PB13);
    for(int i=0;;++i) {
        if(i%100 == 0) {
            oled.clrScr();
            oled.printNumI(enc.getPosition(), 0, 0);
            oled.update();
        }
        enc.poll();
        delay(1);
    }
}

void testClawOnly() {
    claw.deployBridge();
}

void testMenu() {
    Menu m;
    m.run();
}

void testLineFollow() {
    Menu m;
    m.run();
    lineFollower.start();
    Encoder enc(PB14);
    for(int i=0;lineFollower.poll();++i) {
        enc.poll();
        if(i%100 == 0)
        {
            oled.clrScr();
            oled.print("L:", 0, 0);
            oled.print("R:", 0, 10);
            oled.print("E:", 0, 20);
            oled.print("G:", 0, 30);
            oled.print("ER", 0, 40);
            oled.print("EN", 0, 40);
            oled.printNumI(lineFollower.sensorLeftReading, 20, 0);
            oled.printNumI(lineFollower.sensorRightReading, 20, 10);
            oled.printNumI(lineFollower.sensorEdgeReading, 20, 20);
            oled.printNumI(lineFollower.g, 20, 30);
            oled.printNumI(lineFollower.error, 20, 40);
            oled.printNumI(enc.getPosition(), 20, 50);
            oled.update();
        }
    }
    // drop bridge
}

void testPWM() {
    oled.clrScr();
    oled.printNumI(analogRead(PA1), 0, 0);
    oled.printNumI(analogRead(PA3), 0, 10);
    oled.update();
}

void testFFT() {
    oled.clrScr();
    FFTPair fftPair = fft.sample();
    oled.print("1:", 0, 0);
    oled.print("10:", 0, 10);
    oled.printNumI(fftPair.lowAmount, 30, 0);
    oled.printNumI(fftPair.highAmount, 30, 10);
    oled.printNumI(analogRead(Constants::IR_BEACON_PIN), 30, 20);
    oled.printNumI(fft.sampleTime, 50, 30);
    oled.update();
    delay(50);
}

void testEncoders()
{
    Encoder encLeft(PB14);
    Encoder encRight(PB15);

    int32_t before = millis();
    for(int i=0;millis() - before < 10000;++i) {
        Encoder::poll();
        if(i%100 == 0) {
            motor.speed(Constants::MOTOR_LEFT, -Constants::BASE_SPEED.getVal());
            motor.speed(Constants::MOTOR_RIGHT, Constants::BASE_SPEED.getVal());
            oled.clrScr();
            oled.printNumI(encLeft.getPosition(), 0, 0);
            oled.printNumI(encRight.getPosition(), 0, 0);
            oled.update();
        }
    }
}
