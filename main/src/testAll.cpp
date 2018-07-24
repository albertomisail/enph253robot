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
        if(i%200 == 0)
        {
            oled.clrScr();
            oled.print("L:", 0, 0);
            oled.print("R:", 0, 10);
            oled.print("E:", 0, 20);
            oled.print("G:", 0, 30);
            oled.print("ER", 0, 40);
            oled.print("EN", 0, 50);
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

void testEncoders(){


    Encoder encLeft(PB14);
    Encoder encRight(PB15);
    uint8_t OTHER_PIN = PA1;

    int32_t before = millis();
    int32_t b, a;
    for(int32_t i=0;millis() - before < 10000;++i) {
        b=a;
        a = micros();
        Encoder::poll();
        if(i%10000 == 0) {
            motor.speed(Constants::MOTOR_LEFT, -Constants::BASE_SPEED.getVal());
            motor.speed(Constants::MOTOR_RIGHT, Constants::BASE_SPEED.getVal());
            oled.clrScr();
            oled.printNumI(encLeft.getPosition(), 0, 0);
            oled.printNumI(encRight.getPosition(), 0, 10);
            oled.printNumI(analogRead(OTHER_PIN), 0, 20);
            oled.printNumI(a-b, 0, 30);
            oled.update();
        }
    }
}

void testLFandReverse() {
    Menu m;
    m.run();
    lineFollower.start();
    Encoder leftEnc(Constants::LEFT_ENC_PIN);
    Encoder rightEnc(Constants::RIGHT_ENC_PIN);
    oled.invertText(false);
    for(int32_t i=0;lineFollower.poll();++i) {
        //Encoder::poll();
        if(i%10000 == 0)
        {
            oled.clrScr();
            oled.print("L:", 0, 0);
            oled.print("R:", 0, 10);
            oled.print("E:", 0, 20);
            oled.print("G:", 0, 30);
            oled.print("ER", 0, 40);
            oled.print("EN", 0, 50);
            oled.printNumI(lineFollower.sensorLeftReading, 20, 0);
            oled.printNumI(lineFollower.sensorRightReading, 20, 10);
            oled.printNumI(lineFollower.sensorEdgeReading, 20, 20);
            oled.printNumI(lineFollower.sensorLeftReadingAmb, 55, 0);
            oled.printNumI(lineFollower.sensorRightReadingAmb, 55, 10);
            oled.printNumI(lineFollower.sensorEdgeReadingAmb, 55, 20);
            oled.printNumI(lineFollower.sensorLeftReadingPow, 90, 0);
            oled.printNumI(lineFollower.sensorRightReadingPow, 90, 10);
            oled.printNumI(lineFollower.sensorEdgeReadingPow, 90, 20);
            oled.printNumI(lineFollower.g, 20, 30);
            oled.printNumI(lineFollower.error, 20, 40);
            oled.printNumI(leftEnc.getPosition(), 20, 50);
            oled.printNumI(rightEnc.getPosition(), 60, 50);
            oled.printNumI(lineFollower.lastCompTime, 90, 30);
            if(i%20000 == 0)
            {
                oled.print(".", 100, 0);
            }
            oled.update();
        }
    }
    oled.clrScr();
    oled.print("EDGE", 0, 0);
    oled.update();
    delay(500);
    int16_t lastLeftPos = leftEnc.getPosition();
    int16_t lastRightPos = rightEnc.getPosition();
    motor.speed(Constants::MOTOR_LEFT, -Constants::CORRECTION_SPEED);
    motor.speed(Constants::MOTOR_RIGHT, -Constants::CORRECTION_SPEED);

    // Wait for left encoder to
    while(rightEnc.getPosition() - lastRightPos < 6
    && leftEnc.getPosition() - lastLeftPos < 16) {
        Encoder::poll();
    }
    motor.speed(Constants::MOTOR_RIGHT, 0);
    motor.speed(Constants::MOTOR_LEFT, 0);

    delay(1000);

    //Turning to line up with edge and deploy bridge
    motor.speed(Constants::MOTOR_LEFT, -Constants::CORRECTION_SPEED);
    motor.speed(Constants::MOTOR_RIGHT, (Constants::CORRECTION_SPEED)/2);
    int32_t cnt = 0;
    while(leftEnc.getPosition() - lastLeftPos < 16) {
        Encoder::poll();
        if(cnt%10000 == 0) {
            oled.clrScr();
            oled.print("L", 0, 0);
            oled.print("r", 0, 10);
            oled.printNumI(leftEnc.getPosition() - lastLeftPos, 20, 0);
            oled.printNumI(rightEnc.getPosition() - lastRightPos, 20, 10);
            oled.update();
        }
        ++cnt;
    }
    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0); /*
    if(rightEnc.getPosition() - lastRightPos < 12) {
        // probably wanna see what's wrong, in case I'm about to fall off the table
        oled.clrScr();
        oled.print("!!", 0, 0);
        oled.update();
        delay(5000);
    } */
    claw.deployBridge();
    oled.clrScr();
    oled.print("BRIDGE DROPPED", 0, 0);
    oled.update();
    
    delay(2000);

    //Rotating to find Ewok
    motor.speed(Constants::MOTOR_LEFT, Constants::CORRECTION_SPEED/2);
    motor.speed(Constants::MOTOR_RIGHT, -Constants::CORRECTION_SPEED/2);
    while (!infrared.objectDetected()) {
        oled.clrScr();
        oled.printNumI(infrared.makeMeasurement(),0,0);
        oled.update();
    }
    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0);
    oled.print("EWOK DETECTED",0,10);
    oled.update();
    claw.pickEwok();
    delay(10000);
}

void testPickingUpEwok(){
    oled.clrScr();
    oled.update();
    delay(1000);
    oled.clrScr();
    oled.print("STARTING EWOK TEST", 0, 0);
    oled.update();

    delay(1000);
    infrared.init();
    claw.init();
    oled.clrScr();
    oled.print("DONE INITS", 0, 0);
    oled.update();
    delay(1000);

    while(!infrared.objectDetected()) {
        delay(100);
        oled.clrScr();
        oled.printNumI(infrared.makeMeasurement(), 0, 0);
        oled.update();
    }
    oled.print("SAW SOMETHING", 0, 0);
    oled.update();
    delay(1000);
    claw.pickEwok();
    oled.print("EWOK PICKED", 0, 0);
    oled.update();
    delay(500);
}

void testLift(){
    while(true) {
        oled.clrScr();
        oled.print("UP", 0, 0);
        oled.update();
        delay(2000);
        ziplineLift.liftFront();
        delay(2000);
        oled.clrScr();
        oled.print("DOWN", 0, 0);
        oled.update();
        delay(2000);
        ziplineLift.dropFront();
        delay(2000);
    }
}
