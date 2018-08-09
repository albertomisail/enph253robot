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
bool lookForEwok(int threshold, int movementRange, int direction, Movement& mvt, bool secondSweep) {
    bool foundEwok = false;
    mvt.start(direction, -direction, movementRange, movementRange, 80);
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
        if(secondSweep) {
            mvt.start(1,1,2,2,80);
            while(mvt.poll()){}
            mvt.start(-direction, direction, movementRange, movementRange, 80);
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
            motor.speed(Constants::MOTOR_LEFT,0);
            motor.speed(Constants::MOTOR_RIGHT,0);
            delay(2);
            motor.speed(Constants::MOTOR_LEFT, direction*255);
            motor.speed(Constants::MOTOR_RIGHT, -direction*255);
            delay(20);
            motor.speed(Constants::MOTOR_LEFT,0);
            motor.speed(Constants::MOTOR_RIGHT,0);
        }
    }else{
        motor.speed(Constants::MOTOR_LEFT,0);
        motor.speed(Constants::MOTOR_RIGHT,0);
        delay(2);
        motor.speed(Constants::MOTOR_LEFT, -direction*255);
        motor.speed(Constants::MOTOR_RIGHT, direction*255);
        delay(20);
        motor.speed(Constants::MOTOR_LEFT,0);
        motor.speed(Constants::MOTOR_RIGHT,0);
    }
    return foundEwok;
}


bool lookForEwok(int threshold, int movementRange, int direction) {
    Movement mvt;
    return lookForEwok(threshold, movementRange, direction, mvt, true);
}

bool moveForwardToEwok(int threshold, int maxDistance, Movement& mvt) {
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
    delay(2);
    return foundEwok;
}

bool moveForwardToEwok(int threshold, int maxDistance) {
    Movement mvt;
    return moveForwardToEwok(threshold, maxDistance, mvt);
}


void initialLineFollow(Encoder& leftEnc, Encoder& rightEnc) {
    leftEnc.reset();
    rightEnc.reset();
    lineFollower.start(0,0,0);
    for(int32_t i=0;lineFollower.poll();++i) {
        Encoder::poll();
        // if(rightEnc.getPosition()>=130) {
        if(rightEnc.getPosition()>=133) {
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
    lineFollower.powerOffLeds();
    motor.speed(Constants::MOTOR_LEFT,0);
    motor.speed(Constants::MOTOR_RIGHT,0);
    delay(2);
    motor.speed(Constants::MOTOR_LEFT,-255);
    motor.speed(Constants::MOTOR_RIGHT,-255);
    delay(25);
    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0);
    delay(2);
    oled.print("!!", 0, 10);
    oled.update();
}

// /**
//  * Starting from the drop location, get the first ewok, return it to the start,
//  * and get back to the edge. If the ewok isn't found, then give up on it and just
//  * go back to the edge.
//  */
void handleFirstEwok(Encoder& leftEnc, Encoder& rightEnc) {

    Movement mvt;

    bool foundEwok = lookForEwok(Constants::distantInfraredThreshold1, 12, 1);
    oled.clrScr();
    oled.printNumI(foundEwok,0,0);
    oled.update();
    //delay(2000);
    delay(2);

    if(foundEwok) {
        oled.clrScr();
        oled.print("FOUDN EWOK", 0, 0);
        oled.update();
        delay(200);
        // TODO add the method to move foward to toward the
        bool foundEwok2 = moveForwardToEwok(Constants::pickUpInfraredThreshold1, 6);
        mvt.start(1,1,2,2,80);
        while(mvt.poll()){}
        delay(2);
        claw.pickEwok();

        /*oled.clrScr();
        oled.printNumI(foundEwok2,0,10);
        oled.update(); */

        //claw.pickEwok();
        oled.clrScr();
        oled.print("Picked up ewok",0,20);
        oled.update();

        //9 for outside track
        // mvt.move(1,1,9,9,110);
        mvt.move(1,1,11,11,110);
        // mvt.move(-1,-1,13,13,90);
        delay(2);
    }

    //turn off leds
    digitalWrite(Constants::infraredLeds[0], LOW);
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
    //delay(1000);

    lineFollower.findLine(LineFollower::DIR_RIGHT, 80); // blocking
    oled.clrScr();
    oled.print("Done finding line", 0, 0);
    oled.update();

    //mvt.start(1,-1,1,1,80);
    //while(mvt.poll()){}

    //delay(10000);

    leftEnc.reset();
    rightEnc.reset();

    int16_t leftEncPos = leftEnc.getPosition();
    int16_t rightEncPos = rightEnc.getPosition();

    while(lineFollower.poll()) {
        if(leftEnc.getPosition() > 100) {
            break;
        }
    }
    //delay(250);
    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0);
    delay(2);

    oled.clrScr();
    oled.print("Go until the edge", 0, 0);
    oled.update();

    //linefollow until we see the edge
    lineFollower.start(4096, 4096, Constants::EDGE_THRESHOLD.getVal(), 4096, 4096);
    while(lineFollower.poll()){}

    delay(2);

    oled.clrScr();
    oled.print("EDGE!", 0, 0);
    oled.update();

    //backup
    mvt.start(-1, -1, 15,15, 100);
    while(mvt.poll()){};

    delay(2);

    oled.clrScr();
    oled.print("DONE BACKUP", 0, 0);
    oled.update();

    //turn to drop location
    mvt.start(1,-1,20,20,100);
    while(mvt.poll()) {}
    delay(2);

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
    Movement mvt;
    //turn around (left)
    //mvt.start(-1,1,35,35,80);
    //while(mvt.poll()){}
    //Should be 25 for track outside
    // mvt.start(1,-1,25,25,80);
    mvt.start(1,-1,28,28,80);
    while(mvt.poll()){}
    delay(250);
    bridgeServo.write(Constants::positionUnlock);
    mvt.start(-1,-1,4,4,100);
    while(mvt.poll()){}
    delay(2);
    //Add wiggle for track outside
    // motor.speed(Constants::MOTOR_LEFT, 255);
    // motor.speed(Constants::MOTOR_RIGHT, -255);
    // delay(30);
    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0);

    delay(100);
    /*
    motor.speed(Constants::MOTOR_LEFT, 255);
    motor.speed(Constants::MOTOR_RIGHT, 255);
    delay(20);
    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0);
    delay(2); */
    //Go forward so that bridge drops
    mvt.start(1,1,5,5,110);
    while(mvt.poll()){}
    // old method:
    // mvt.move(-1, 1, 2, 2, 80);
    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0);
    delay(2);

    motor.speed(Constants::MOTOR_LEFT, -150);
    motor.speed(Constants::MOTOR_RIGHT, 150);
    delay(20);

    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0);
    delay(2);


    //go backwards across the bridge
    mvt.start(-1,-1,52,52,80);
    while(mvt.poll()){}
    delay(500);
    mvt.start(-1,-1,2,10,80);
    while(mvt.poll()){}
    delay(500);
}

void handleSecondEwok(){
    Movement mvt;

    mvt.start(-1,1,23,23,80);
    while(mvt.poll()){}
    delay(500);

    //Should be 7 for track outside
    mvt.start(1,1,6,6,80);
    // mvt.start(1,1,7,7,80);
    while(mvt.poll()){}

    bool foundEwok = lookForEwok(Constants::distantInfraredThreshold2, 18, -1);
    oled.clrScr();
    oled.printNumI(foundEwok,0,0);
    oled.update();
    delay(200);

    if(foundEwok) {
        // TODO add the method to move foward to toward the ewok
        bool foundEwok2 = moveForwardToEwok(Constants::pickUpInfraredThreshold2, 10);
        mvt.start(1,1,3,3,80);
        while(mvt.poll()){}

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
}

void maneuverToSecondDropLocation(Encoder& leftEnc, Encoder& rightEnc){
    leftEnc.reset();
    rightEnc.reset();

    lineFollower.start(0,0,0);
    while(lineFollower.poll()) {
        Encoder::poll();
        if(leftEnc.getPosition() > 175) {
            break;
        }
    }
    lineFollower.start();
    while(lineFollower.poll()) {}
    motor.speed(Constants::MOTOR_LEFT,0);
    motor.speed(Constants::MOTOR_RIGHT,0);
    delay(2);
    motor.speed(Constants::MOTOR_LEFT, -255);
    motor.speed(Constants::MOTOR_RIGHT, -255);
    delay(30);
    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0);

    Movement mvt;
    mvt.start(-1, -1, 35, 35, 100);
    while(mvt.poll()){}
    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0);
    delay(250);

    mvt.start(-1,1,16,16,80);
    while(mvt.poll()){}
    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0);
    delay(250);

    int32_t timeLimit = millis()+1500;

    mvt.start(1,1,15,15,80);
    while(mvt.poll()){
        if(millis() > timeLimit) break;
    }
    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0);
}

void handleThirdEwok(){
    Movement mvt;
    mvt.start(-1,-1,10,10,80);
    while(mvt.poll()){}
    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0);

    delay(2);

    lineFollower.findLine(LineFollower::DIR_RIGHT, 90);

    mvt.move(-1, -1, 6, 6, 80);

    // mvt.start(1,-1,5,5,80);
    // while(mvt.poll()){}
    // motor.speed(Constants::MOTOR_LEFT, 0);
    // motor.speed(Constants::MOTOR_RIGHT, 0);

    delay(200);

    bool foundEwok = lookForEwok(Constants::distantInfraredThreshold3, 12, -1);
    oled.clrScr();
    oled.printNumI(foundEwok,0,0);
    oled.update();
    delay(200);

    if(foundEwok) {
        // TODO add the method to move foward to toward the ewok
        bool foundEwok2 = moveForwardToEwok(Constants::pickUpInfraredThreshold3, 0);
        mvt.start(1,1,1,1,80);
        while(mvt.poll()){}
        oled.clrScr();
        oled.printNumI(foundEwok2,0,10);
        oled.update();

        claw.pickEwok();
        oled.clrScr();
        oled.print("Picked up ewok",0,20);
        oled.update();
    }

    mvt.move(-1, -1, 5, 5, 80);

    //turn off leds
    digitalWrite(Constants::infraredLeds[0], LOW);

    mvt.start(-1,1,10,10,80);
    while(mvt.poll()){}

    motor.speed(Constants::MOTOR_LEFT,0);
    motor.speed(Constants::MOTOR_RIGHT,0);
    delay(2);

    mvt.start(1, 1, 20, 20, 80);
    int32_t timeout = millis()+1000;
    while(mvt.poll()){
        if(timeout < millis()) break;
    }
    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0);
}

void maneuverToSecondBridge() {
    Movement mvt;
    mvt.move(-1, -1, 5, 5, 100);
    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0);
    delay(2);
    lineFollower.findLine(LineFollower::DIR_RIGHT, 80);
    delay(2);
    lineFollower.start();
    while(lineFollower.poll()) {}
    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0);
    delay(2);
    motor.speed(Constants::MOTOR_LEFT, -255);
    motor.speed(Constants::MOTOR_RIGHT, -255);
    delay(25);
    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0);
    delay(2);

    // Choice 1: Align with edge first then rotate 90 degrees and backup to drop bridge
    //lineFollower.alignWithEdge();
    // delay(10000);

    mvt.move(-1, -1, 13, 13, 90);
    delay(2);
    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0);
    delay(2);
    motor.speed(Constants::MOTOR_LEFT, 255);
    motor.speed(Constants::MOTOR_RIGHT, 255);
    delay(20);
    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0);
    delay(2);

    mvt.move(-1, 1, 16, 16, 90);
    delay(2);
    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0);
    delay(2);
    motor.speed(Constants::MOTOR_LEFT, 255);
    motor.speed(Constants::MOTOR_RIGHT, -255);
    delay(20);
    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0);
    delay(2);

    int32_t t = millis() + 1500;
    mvt.start(1,1,36,36,80);
    while(mvt.poll()) {
        if(t < millis()) break;
    }

    t = millis() + 1000;
    mvt.start(1,1,12,12,180);
    while(mvt.poll()) {
        if(t < millis()) break;
    }
    // delay(5000);
    motor.speed(Constants::MOTOR_RIGHT, 0);
    delay(2);

    mvt.move(-1, -1, 53,53, 90);
    delay(2);
    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0);
    delay(2);
    motor.speed(Constants::MOTOR_LEFT, 255);
    motor.speed(Constants::MOTOR_RIGHT, 255);
    delay(20);
    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0);
    delay(2);

    // //Choice 2: Rotate 90 degrees, lineup with gap edge and rotate 180 then drop bridge
    // mvt.move(-1, -1, 13, 13, 90);
    // delay(2);
    // motor.speed(Constants::MOTOR_LEFT, 0);
    // motor.speed(Constants::MOTOR_RIGHT, 0);
    // delay(2);
    // motor.speed(Constants::MOTOR_LEFT, 255);
    // motor.speed(Constants::MOTOR_RIGHT, 255);
    // delay(20);
    // motor.speed(Constants::MOTOR_LEFT, 0);
    // motor.speed(Constants::MOTOR_RIGHT, 0);
    // delay(2);

    // mvt.move(1, -1, 16, 16, 90);
    // delay(2);
    // motor.speed(Constants::MOTOR_LEFT, 0);
    // motor.speed(Constants::MOTOR_RIGHT, 0);
    // delay(2);
    // motor.speed(Constants::MOTOR_LEFT, -255);
    // motor.speed(Constants::MOTOR_RIGHT, 255);
    // delay(20);
    // motor.speed(Constants::MOTOR_LEFT, 0);
    // motor.speed(Constants::MOTOR_RIGHT, 0);
    // delay(2);

    // delay(1000);

    // mvt.move(1, 1, 26, 26, 90);
    // delay(2);
    // motor.speed(Constants::MOTOR_LEFT, 0);
    // motor.speed(Constants::MOTOR_RIGHT, 0);
    // delay(2);
    // motor.speed(Constants::MOTOR_LEFT, -255);
    // motor.speed(Constants::MOTOR_RIGHT, -255);
    // delay(20);
    // motor.speed(Constants::MOTOR_LEFT, 0);
    // motor.speed(Constants::MOTOR_RIGHT, 0);
    // delay(2);

    // delay(1000);

    // lineFollower.alignWithEdge();
    // delay(1000);

    // mvt.move(1, -1, 29, 29, 90);
    // delay(2);
    // motor.speed(Constants::MOTOR_LEFT, 0);
    // motor.speed(Constants::MOTOR_RIGHT, 0);
    // delay(2);
    // motor.speed(Constants::MOTOR_LEFT, -255);
    // motor.speed(Constants::MOTOR_RIGHT, 255);
    // delay(20);
    // motor.speed(Constants::MOTOR_LEFT, 0);
    // motor.speed(Constants::MOTOR_RIGHT, 0);
    // delay(2);

    // mvt.move(-1, -1, 7, 7, 90);
    // delay(2);
    // motor.speed(Constants::MOTOR_LEFT, 0);
    // motor.speed(Constants::MOTOR_RIGHT, 0);
    // delay(2);
    // motor.speed(Constants::MOTOR_LEFT, 255);
    // motor.speed(Constants::MOTOR_RIGHT, 255);
    // delay(20);
    // motor.speed(Constants::MOTOR_LEFT, 0);
    // motor.speed(Constants::MOTOR_RIGHT, 0);
    // delay(2);

    delay(1000);
    bridgeServo.write(Constants::positionSecondUnlock);


    // mvt.start(1,1,3,3,110);
    // while(mvt.poll()){}
    // motor.speed(Constants::MOTOR_LEFT, 0);
    // motor.speed(Constants::MOTOR_RIGHT, 0);

    delay(900);

    int32_t timeout = millis() + 1500;
    mvt.start(-1,-1,8,8,80);
    while(mvt.poll()) {
        if(timeout < millis()) break;
    }

    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0);

    mvt.move(1, 1, 8, 8, 80);

    mvt.move(-1, -1, 43, 43, 170);

}

void handleFourthEwok() {
    Movement mvt;
    mvt.move(-1,1,25,25,80);
    MovementInstruction initialTurnReverse = mvt.reverseLast();

    bool foundEwok = lookForEwok(Constants::distantInfraredThreshold4, 15, -1, mvt, false);
    MovementInstruction reverseLook = mvt.reverseLast();
    oled.clrScr();
    oled.printNumI(foundEwok,0,0);
    oled.update();
    //delay(2000);
    delay(2);

    if(foundEwok) {
        // TODO add the method to move foward to toward the
        bool foundEwok2 = moveForwardToEwok(Constants::pickUpInfraredThreshold4, 6, mvt);
        MovementInstruction reverseFromEwok = mvt.reverseLast();
        mvt.start(1,1,-2,-2,80);
        while(mvt.poll()){}
        delay(2);
        claw.pickEwok();

        oled.clrScr();
        oled.printNumI(foundEwok2,0,10);
        oled.update();

        //claw.pickEwok();
        oled.clrScr();
        oled.print("Picked up ewok",0,20);
        oled.update();

        mvt.move(reverseFromEwok);
    }
    // mvt.move(1,-1,24,24,80);
    // delay(1000);
    // mvt.move(1,1,35,35,80);
    //

    mvt.move(1, 1, 8, 8, 80);

    reverseLook.leftAmt--;
    reverseLook.rightAmt--;
    mvt.move(reverseLook);
    mvt.move(initialTurnReverse);

    motor.speed(Constants::MOTOR_LEFT, -initialTurnReverse.leftDir*255);
    motor.speed(Constants::MOTOR_RIGHT, -initialTurnReverse.rightDir*255);
    delay(15);
    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0);
    delay(2);

    mvt.move(1, 1, 80, 80, 90);
    lineFollower.findLine(LineFollower::DIR_RIGHT, 80);
    delay(2);
    lineFollower.start();
    while(lineFollower.poll());
    mvt.move(-1, -1, 8, 8, 80);
    mvt.move(-1, 1, 16, 16, 80);
    int timeout = millis() + 2000;
    mvt.start(1, 1, 30, 30, 80);
    while(mvt.poll() && millis() < timeout) {}
    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0);
    delay(2);
    claw.dropEwok();
}

void mainRun() {
    bridgeServo.attach(Constants::BRIDGE_SERVO_PIN);
    bridgeServo.write(Constants::positionLock);
    //Menu m;
    //m.run();
    Encoder leftEnc(Constants::LEFT_ENC_PIN);
    Encoder rightEnc(Constants::RIGHT_ENC_PIN);

    oled.invertText(false);

    // handleFirstEwok(leftEnc, rightEnc);
    // while(true) {}

    initialLineFollow(leftEnc, rightEnc);

    oled.clrScr();
    oled.print("Initial line follow", 0, 0);
    oled.update();

    //delay(2000);

    handleFirstEwok(leftEnc, rightEnc);

    oled.clrScr();
    oled.print("First ewok handled", 0, 0);
    oled.update();

    //delay(2000);

    maneuverToDropLocation(leftEnc, rightEnc);

    oled.clrScr();
    oled.print("Maneuvered to drop location",0,0);
    oled.update();

    //delay(2000);

    claw.dropEwok();


    oled.clrScr();
    oled.print("Ewok droped",0,0);
    oled.update();

    //delay(2000);

    maneuverToBridge();

    oled.clrScr();
    oled.print("Manuvered to bridge", 0, 0);
    oled.update();

    delay(200);

    deployBridge();

    handleSecondEwok();

    maneuverToIR();

    //delay(1000);

    IRBeacon();
    // delay(5000);

    maneuverToSecondDropLocation(leftEnc, rightEnc);

    //delay(1000);

    claw.dropEwok();

    //delay(1000);

    handleThirdEwok();

    claw.dropEwok();

    maneuverToSecondBridge();

    handleFourthEwok();

    delay(10000);
}

void oneEwokRun() {
    // TODO
}
