#include "procedures.h"
#include <Arduino.h>
#include <Menu.h>
#include <LineFollower.h>
#include <Encoder.h>
#include <ClawBase.h>
#include <Movement.h>
#include <InfraredBase.h>
#include <FFT.h>

Servo bridgeServo;

//1 for left to right -1 for right to left
bool lookForEwok(int threshold, int movementRange, int direction) {
    bool foundEwok = false;
    Movement mvt;
    mvt.start(direction, -direction, movementRange, movementRange, 100);
    infrared.startMeasurement();
    while(mvt.poll()) {
        if(!infrared.poll()) {
            if(infrared.objectDetected(threshold)){
                foundEwok = true;
                break;
            }
            infrared.startMeasurement();
        }
    }
    if(!foundEwok){
        mvt.start(1,1,2,2,80);
        while(mvt.poll()){}
        mvt.start(-direction, direction, movementRange, movementRange, 100);
        infrared.startMeasurement();
        while(mvt.poll()) {
            if(!infrared.poll()) {
                if(infrared.objectDetected(threshold)){
                    foundEwok = true;
                    break;
                }
                infrared.startMeasurement();
            }
        }
        motor.speed(Constants::MOTOR_LEFT, direction*255);
        motor.speed(Constants::MOTOR_RIGHT, -direction*255);
        delay(20);
        motor.speed(Constants::MOTOR_LEFT,0);
        motor.speed(Constants::MOTOR_RIGHT,0);
    }else{
        motor.speed(Constants::MOTOR_LEFT, -direction*255);
        motor.speed(Constants::MOTOR_RIGHT, direction*255);
        delay(20);
        motor.speed(Constants::MOTOR_LEFT,0);
        motor.speed(Constants::MOTOR_RIGHT,0);
    }
    return foundEwok;
}

bool moveForwardToEwok(int threshold, int maxDistance) {
    Movement mvt;
    bool foundEwok = false;
    mvt.start(1, 1, maxDistance, maxDistance, 90);
    infrared.startMeasurement();
    while(mvt.poll()) {
        if(!infrared.poll()) {
            if(infrared.lastMeasurement() > threshold) {
                foundEwok = true;
                break;
            }
            infrared.startMeasurement();
        }
    }
    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0);
    return foundEwok;
}

void initialLineFollow(Encoder& leftEnc, Encoder& rightEnc) {
    leftEnc.reset();
    rightEnc.reset();
    lineFollower.start(0,0,0);
    for(int32_t i=0;lineFollower.poll();++i) {
        Encoder::poll();
        if(rightEnc.getPosition()>=140) {
            oled.clrScr();
            oled.print("!! 135", 0, 0);
            oled.update();
            break;
        }
        if(i%10000 == 0)
        {
            oled.clrScr();
            oled.print(const_cast<char*>("L:"), 0, 0);
            oled.print(const_cast<char*>("R:"), 0, 10);
            oled.print(const_cast<char*>("E:"), 0, 20);
            oled.print(const_cast<char*>("G:"), 0, 30);
            oled.print(const_cast<char*>("ER"), 0, 40);
            oled.print(const_cast<char*>("EN"), 0, 50);
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
                oled.print(const_cast<char*>("."), 100, 0);
            }
            oled.update();
        }
    }
    motor.speed(Constants::MOTOR_LEFT,-255);
    motor.speed(Constants::MOTOR_RIGHT,-255);
    delay(25);
    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0);
    oled.print("!!", 0, 10);
    oled.update();
}

// /**
//  * Starting from the drop location, get the first ewok, return it to the start,
//  * and get back to the edge. If the ewok isn't found, then give up on it and just
//  * go back to the edge.
//  */
bool handleFirstEwok(Encoder& leftEnc, Encoder& rightEnc) {

    Movement mvt;

    bool foundEwok = lookForEwok(Constants::distantInfraredThreshold1, 12, 1);
    oled.clrScr();
    oled.printNumI(foundEwok,0,0);
    oled.update();
    delay(2000);

    bool foundEwok2 = false;
    if(foundEwok) {
        // TODO add the method to move foward to toward the ewok
        foundEwok2 = moveForwardToEwok(Constants::pickUpInfraredThreshold1, 10);

        oled.clrScr();
        oled.printNumI(foundEwok2,0,10);
        oled.update();

        claw.pickEwok();
        oled.clrScr();
        oled.print("Picked up ewok",0,20);
        oled.update();

        mvt.move(1,1,9,9,110);
    }

    //turn off leds
    digitalWrite(Constants::infraredLeds[0], LOW);
    return foundEwok2;
}

/**
 * Starting from the edge, maneuver to the location where the ewok is dropped.
 */
void maneuverToDropLocation(Encoder& leftEnc, Encoder& rightEnc) {
    Movement mvt;
    mvt.start(1, -1, 17, 17, 100);
    while(mvt.poll()){}
    // go back to the start

    oled.clrScr();
    oled.print("About to find line", 0, 0);
    oled.update();
    delay(1000);

    lineFollower.findLine(LineFollower::DIR_RIGHT, 80); // blocking
    oled.clrScr();
    oled.print("Done finding line", 0, 0);
    oled.update();

    delay(1000);

    leftEnc.reset();
    rightEnc.reset();

    int16_t leftEncPos = leftEnc.getPosition();
    int16_t rightEncPos = rightEnc.getPosition();

    lineFollower.start();
    while(lineFollower.poll()) {
        if(leftEnc.getPosition() > 100) {
            break;
        }
    }

    oled.clrScr();
    oled.print("Go until the edge", 0, 0);
    oled.update();

    //linefollow until we see the edge
    lineFollower.start(4096, 4096, Constants::EDGE_THRESHOLD.getVal(), 4096, 4096);
    while(lineFollower.poll()){}

    oled.clrScr();
    oled.print("EDGE!", 0, 0);
    oled.update();

    //backup
    mvt.start(-1, -1, 10,10, 100);
    while(mvt.poll()){};

    oled.clrScr();
    oled.print("DONE BACKUP", 0, 0);
    oled.update();

    //turn to drop location
    mvt.start(1,-1,20,20,100);
    while(mvt.poll()) {}

    oled.clrScr();
    oled.print("DROP LOCATION, ABOUT TO DROP", 0, 0);
    oled.update();
}

void maneuverToBridge() {
    Movement mvt;

    lineFollower.findLine(LineFollower::DIR_RIGHT, 80);

    lineFollower.start();
    while(lineFollower.poll()) {}
}

void deployBridge(){
    Encoder leftEnc(Constants::LEFT_ENC_PIN);
    Encoder rightEnc(Constants::RIGHT_ENC_PIN);
    Movement mvt;
    mvt.start(1,-1,26,26,100);
    int32_t cc = 0;
    while(mvt.poll()){
        if((++cc)%10000 == 0) {
            oled.clrScr();
            oled.print("LEFT :", 0, 0);
            oled.print("RIGHT:", 0, 10);
            oled.printNumI(leftEnc.getPosition(), 50, 0);
            oled.printNumI(rightEnc.getPosition(), 50, 10);
            oled.update();
        }
    }
    motor.speed(Constants::MOTOR_LEFT, 255);
    motor.speed(Constants::MOTOR_RIGHT, -255);
    delay(20);
    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0);
    delay(500);
    mvt.start(-1,-1,3,3,100);
    while(mvt.poll()){}
    delay(500);
    // motor.speed(Constants::MOTOR_LEFT, 255);
    // motor.speed(Constants::MOTOR_RIGHT, 255);
    // delay(30);
    // motor.speed(Constants::MOTOR_LEFT, 0);
    // motor.speed(Constants::MOTOR_RIGHT, 0);

    bridgeServo.write(Constants::positionUnlock);
    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0);
    delay(100);
    //Go forward so that bridge drops
    motor.speed(Constants::MOTOR_LEFT, 255);
    motor.speed(Constants::MOTOR_RIGHT, 255);
    delay(80);
    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0);
    delay(2);
    motor.speed(Constants::MOTOR_LEFT, -255);
    motor.speed(Constants::MOTOR_RIGHT, -255);
    delay(30);
    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0);

    //go backwards across the bridge
    mvt.start(-1,-1,57,62,80);
    while(mvt.poll()){}
    delay(500);
}

void handleSecondEwok(){
    Movement mvt;

    mvt.start(-1,1,23,23,80);
    while(mvt.poll()){}
    delay(500);

    bool foundEwok = lookForEwok(Constants::distantInfraredThreshold2, 18, -1);
    oled.clrScr();
    oled.printNumI(foundEwok,0,0);
    oled.update();
    delay(2000);

    if(foundEwok) {
        // TODO add the method to move foward to toward the ewok
        bool foundEwok2 = moveForwardToEwok(Constants::pickUpInfraredThreshold2, 10);

        oled.clrScr();
        oled.printNumI(foundEwok2,0,10);
        oled.update();

        claw.pickEwok();
        oled.clrScr();
        oled.print("Picked up ewok",0,20);
        oled.update();
    }

    //turn off leds
    digitalWrite(Constants::infraredLeds[0], LOW);
}

void IRBeacon() {
    fft.init();
    digitalWrite(Constants::MULTIPLEXER_PIN, LOW);
    float f10, f1;
    int32_t last1kTime = millis()-1000;
    int seen1k = 0, seen10k = 0;
    int cnt = 0;
    while(true) {
        f1=0,f10=0;
        int32_t ha, la;
        for(int i=0;i<20;++i) {
            FFTPair fftPair = fft.sample();
            f10 += fftPair.highAmount;
            f1 += fftPair.lowAmount;
            ha = fftPair.highAmount;
            la = fftPair.lowAmount;
        }
        if((++cnt)%1 == 0) {
            oled.clrScr();
            oled.print("1K :", 0, 0);
            oled.print("10K:", 0, 10);
            oled.printNumI(f1, 30, 0);
            oled.printNumI(f10, 30, 10);
            oled.printNumI(la, 90, 0);
            oled.printNumI(ha, 90, 10);
            oled.update();
        }
        float totalAmount = sqrt(f10*f10 + f1*f1);
        if(totalAmount > Constants::FFT_THRESHOLD_TOTAL)
        {
            // if(f10 > f1) {
            //     seen1k = 0;
            //     if(++seen10k > 1) {
            //         if(millis()-last1kTime < 500) {
            //             break;
            //         }
            //     }
            // } else {
            //     seen10k=0;
            //     if(seen1k > 1) {
            //         last1kTime = millis();
            //     }
            // }
            //
            if(f10 != 0 && f1/f10 > Constants::FFT_THRESHOLD_1K_FACTOR) {
                last1kTime = millis();
            }
            if(f1 != 0 && f10/f1 > Constants::FFT_THRESHOLD_10K_FACTOR
            && millis()-last1kTime < 200) {
                break;
            }
        }
        delay(10);
    }

    oled.clrScr();
    oled.print("got 10khz!", 0, 0);
    oled.update();
}
void maneuverToIR(){
    lineFollower.findLine(LineFollower::DIR_LEFT, 80);
    Movement mvt;
    mvt.move(-1, 1, 1, 1, 120);
}

void maneuverToSecondDropLocation(Encoder& leftEnc, Encoder& rightEnc){
    leftEnc.reset();
    rightEnc.reset();

    lineFollower.start(0,0,0);
    while(lineFollower.poll()) {
        Encoder::poll();
        if(leftEnc.getPosition() > 140) {
            break;
        }
    }
    lineFollower.start();
    while(lineFollower.poll()) {}
    motor.speed(Constants::MOTOR_LEFT, -255);
    motor.speed(Constants::MOTOR_RIGHT, -255);
    delay(30);
    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0);

    Movement mvt;
    mvt.move(-1, -1, 35, 35, 100);


    // leftEnc.reset();
    // rightEnc.reset();
    //
    // lineFollower.start();
    // while(lineFollower.poll()) {
    //     Encoder::poll();
    //     if(leftEnc.getPosition() > 160) {
    //         break;
    //     }
    // }
    // motor.speed(Constants::MOTOR_LEFT, 0);
    // motor.speed(Constants::MOTOR_RIGHT, 0);
    //
    // delay(500);
    //
    // Movement mvt;
    // mvt.start(-1,1,16,16,80);
    // while(mvt.poll()){}
    // motor.speed(Constants::MOTOR_LEFT, 0);
    // motor.speed(Constants::MOTOR_RIGHT, 0);
    //
    // delay(500);
    //
    // int32_t timeLimit = millis()+2000;
    //
    // mvt.start(1,1,5,5,80);
    // while(mvt.poll()){
    //     if(millis() > timeLimit) break;
    // }
    // motor.speed(Constants::MOTOR_LEFT, 0);
    // motor.speed(Constants::MOTOR_RIGHT, 0);
}

void handleThirdEwok(){
    Movement mvt;
    //mvt.start(-1,-1,10,10,80);
    while(mvt.poll()){}
    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0);

    delay(200);

    lineFollower.findLine(LineFollower::DIR_RIGHT, 90);

    // mvt.start(1,-1,5,5,80);
    // while(mvt.poll()){}
    // motor.speed(Constants::MOTOR_LEFT, 0);
    // motor.speed(Constants::MOTOR_RIGHT, 0);

    delay(200);

    bool foundEwok = lookForEwok(Constants::distantInfraredThreshold3, 12, -1);
    oled.clrScr();
    oled.printNumI(foundEwok,0,0);
    oled.update();
    delay(2000);

    if(foundEwok) {
        // TODO add the method to move foward to toward the ewok
        bool foundEwok2 = moveForwardToEwok(Constants::pickUpInfraredThreshold3, 10);

        oled.clrScr();
        oled.printNumI(foundEwok2,0,10);
        oled.update();

        claw.pickEwok();
        oled.clrScr();
        oled.print("Picked up ewok",0,20);
        oled.update();
    }

    //turn off leds
    digitalWrite(Constants::infraredLeds[0], LOW);

    mvt.start(-1,1,10,10,80);
    while(mvt.poll()){}

    mvt.start(1, 1, 5, 5, 80);
    int32_t timeout = millis()+1500;
    while(mvt.poll()){
        if(timeout < millis()) break;
    }
    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0);
}

void mainRun() {
    bridgeServo.attach(Constants::BRIDGE_SERVO_PIN);
    bridgeServo.write(Constants::positionLock);
    //Menu m;
    //m.run();
    Encoder leftEnc(Constants::LEFT_ENC_PIN);
    Encoder rightEnc(Constants::RIGHT_ENC_PIN);
    oled.invertText(false);
    delay(5000);

    // initialLineFollow(leftEnc, rightEnc);
    //
    // oled.clrScr();
    // oled.print("Initial line follow", 0, 0);
    // oled.update();
    //
    // delay(2000);
    //
    // handleFirstEwok(leftEnc, rightEnc);
    //
    // oled.clrScr();
    // oled.print("First ewok handled", 0, 0);
    // oled.update();
    //
    // delay(2000);
    //
    // maneuverToDropLocation(leftEnc, rightEnc);
    //
    // oled.clrScr();
    // oled.print("Maneuvered to drop location",0,0);
    // oled.update();
    //
    // delay(2000);
    //
    // claw.dropEwok();
    //
    // oled.clrScr();
    // oled.print("Ewok droped",0,0);
    // oled.update();
    //
    // delay(2000);

    //maneuverToBridge();

    // oled.clrScr();
    // oled.print("Manuvered to bridge", 0, 0);
    // oled.update();
    //
    // delay(2000);

    deployBridge();

    handleSecondEwok();

    maneuverToIR();

    delay(1000);

    IRBeacon();
    // delay(5200);

    maneuverToSecondDropLocation(leftEnc, rightEnc);

    delay(1000);

    claw.dropEwok();

    delay(1000);

    handleThirdEwok();

    claw.dropEwok();

    delay(10000);
}

void oneEwokRun() {
    // TODO
}
