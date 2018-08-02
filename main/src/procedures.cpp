#include "procedures.h"
#include <Arduino.h>
#include <Menu.h>
#include <LineFollower.h>
#include <Encoder.h>
#include <ClawBase.h>
#include <Movement.h>
#include <InfraredBase.h>
#include <FFT.h>
#include <Bridge.h>

bool lookForEwok(int threshold, int movementRange, int forwardAmount, int tries) {
    bool foundEwok = false;
    Movement mvt;
    tries = 1;
    for(int i=0;i<tries;++i) {

        /*mvt.start(-1, 1, movementRange/2, movementRange/2, 120);
        while(mvt.poll()) {} */

        mvt.start(1, -1, movementRange, movementRange, 100);
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
        if(foundEwok) {
            break;
        }
        // these ones go faster cause they don't need to look for ewoks
        /*
        mvt.start(1, 1, forwardAmount, forwardAmount, 120);
        while(mvt.poll()) {}
        mvt.start(-1, 1, movementRange-movementRange/2, movementRange-movementRange/2, 120);
        while(mvt.poll()) {}
        */
    }
    motor.speed(Constants::MOTOR_LEFT, -255);
    motor.speed(Constants::MOTOR_RIGHT, 255);
    delay(20);
    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0);
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
    lineFollower.start();
    for(int32_t i=0;lineFollower.poll();++i) {
        Encoder::poll();
        if(rightEnc.getPosition()>=135) {
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
    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0);
    oled.print("!!", 0, 10);
    oled.update();
}

/**
 * Starting from the edge, maneuver to the location where the bridge is dropped.
 */
void maneuverToDropLocation(Encoder& leftEnc, Encoder& rightEnc) {
    Movement mvt;
    mvt.start(1, -1, 12, 12, 100);
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
    motor.stop(Constants::MOTOR_LEFT);
    motor.stop(Constants::MOTOR_RIGHT);
}

// void maneuverToBridge() {
//     Movement mvt;
//     // ~120 degree turn to face toward ewok
//     mvt.start(-1,-1,6,6,100);
//     while(mvt.poll()){}
// 	delay(500);
//     mvt.start(-1,1,8,8,100);
//     while(mvt.poll()){}
// 	delay(500);
//     mvt.start(-1,-1,6,6,100);
//     while(mvt.poll()){}
// 	delay(500);
//     mvt.start(1,-1,4,4,100);
//     while(mvt.poll()){}
// 	delay(500);
//     mvt.start(1,1,40,40,100);
//     while(mvt.poll()){}
// }

// /**
//  * Starting from the drop location, get the first ewok, return it to the start,
//  * and get back to the edge. If the ewok isn't found, then give up on it and just
//  * go back to the edge.
//  */
void handleFirstEwok(Encoder& leftEnc, Encoder& rightEnc) {

    Movement mvt;
    // // ~120 degree turn to face toward ewok
    // mvt.start(1,-1,6,6,90);
    // while(mvt.poll()){}
    // mvt.start(-1,-1,14,14,90);
    // while(mvt.poll()){}
    // mvt.start(1, -1, 3, 3, 90);
    // while(mvt.poll()){}

    // mvt.start(1, -1, 20, 20, 80);
    // while(mvt.poll()){}

    bool foundEwok = lookForEwok(Constants::distantInfraredThreshold1, 6, 3, 5);
    oled.clrScr();
    oled.printNumI(foundEwok,0,0);
    oled.update();
    delay(5000);

    if(foundEwok) {
        // TODO add the method to move foward to toward the ewok
        bool foundEwok2 = moveForwardToEwok(Constants::pickUpInfraredThreshold1, 10);

        oled.clrScr();
        oled.printNumI(foundEwok2,0,10);
        oled.update();

        claw.pickEwok();
        oled.clrScr();
        oled.print("Picked up ewok",0,20);
        oled.update();
        //
        // mvt.start(1, 1, 9, 9, 110);
        // while(mvt.poll()){}
        //
        //
        // mvt.start(-1, 1, 12, 12, 100);
        // while(mvt.poll()){}
        // // go back to the start
        //
        // oled.print("About to find line", 0, 0);
        // oled.update();
        // delay(1000);
        //
        // lineFollower.findLine(LineFollower::DIR_LEFT, 100); // blocking
        // oled.print("Done finding line", 0, 0);
        // oled.update();
        //
        // delay(1000);
        //
        // leftEnc.reset();
        // rightEnc.reset();
        //
        // int16_t leftEncPos = leftEnc.getPosition();
        // int16_t rightEncPos = rightEnc.getPosition();
        //
        // oled.clrScr();
        // oled.printNumI(leftEncPos, 0, 0);
        // oled.printNumI(rightEncPos, 50, 0);
        // oled.update();
        //
        // lineFollower.start(0,0,0);
        //
        // // TODO determine distance to end of track when returning first ewok
        // // OR write a better method of finding the end for example, line follow for
        // // 90 steps, then go straight until edge detected. Then reverse by 40.
        // while(lineFollower.poll()) {
        //     if(leftEnc.getPosition() > 40) {
        //         break;
        //     }
        // }
        //
        // lineFollower.start();
        // while(lineFollower.poll()) {
        //     if(leftEnc.getPosition() > 90) {
        //         break;
        //     }
        // }
        //
        // mvt.start(1, 1, 20, 20, 100);
        // while(mvt.poll()){};
        //
        // // TODO write the drop ewok method
        // claw.dropEwok();
        //
        // lineFollower.findLine(LineFollower::DIR_RIGHT, 80);
        // lineFollower.start();
        // while(lineFollower.poll()) {} // go until we get to the edge
    } else {
        // go back onto the line and follow until the edge
        // mvt.start(-1, 1, 8, 8, 100);
        // while(mvt.poll()) {}
        // mvt.start(-1, -1, 40, 40, 100);
        // while(mvt.poll()) {}
        // mvt.start(1, -1, 8, 8, 100);
        // while(mvt.poll()) {}
        //
        // // follow the line until the end
        // lineFollower.findLine(LineFollower::DIR_LEFT, 80);
        // lineFollower.start();
        // while(lineFollower.poll()) {}
    }
}

// /**
//  * Start right before the bridge; cross, then turn right.  Stop at about where
//  * the second ewok should be.
//  */
// void getToSecondEwok() {
//     Movement move;
//     move.start(1, 1, 48, 40, 100);
//     while(move.poll()) {}
//     delay(500);
//     move.start(1, -1, 6, 6, 90);
//     while(move.poll()) {}
//     delay(500);
//     move.start(1, 1, 24, 24, 90);
//     while(move.poll()) {}
//     delay(500);
// }

// /**
//  * Look for the ewok, pick it up if possible.  If not, return false.
//  */
// bool handleSecondEwok() {
//     // TODO
//     bool foundEwok = lookForEwok(Constants::distantInfraredThreshold2, 6, 3, 4);
//     if(!foundEwok) return false;
//     foundEwok = moveForwardToEwok(Constants::pickUpInfraredThreshold2, 6);
//     if(claw.pickEwok()) return true;
//     Movement mvt;
//     mvt.start(-1, -1, 1, 1, 100);
//     return claw.pickEwok();
// }

// /**
//  * After seeeing the beacon, try to cross the arch as quickly as possible
//  * Continue until seenig an edge.
//  */
// void crossArch() {
//     lineFollower.findLine(LineFollower::DIR_LEFT, 100);
//     lineFollower.start();
//     while(lineFollower.poll()) {}
//     // TODO: do we need to slow down at the end, so we don't go off the edge?
// }

// /**
//  * From the second edge, reverse and navigate to edge in order to drop second ewok.
//  * Drop the ewok if we actually have it.
//  */
// void dropSecondEwok(boolean haveSecondEwok) {
//     Movement mvt;
//     mvt.start(-1, -1, 40, 40, 100);
//     while(mvt.poll()) {}
//     mvt.start(-1, 1, 6, 6, 100);

//     // TODO: make ~2s timeout or something like that for this forward movement,
//     // so if we bump into the wal, we won't wait forever
//     // OR we can look for the wall behind it.
//     mvt.start(1, 1, 10, 10, 100);
//     if(haveSecondEwok) {
//         claw.dropEwok();
//     }
// }

// void handleThirdEwok() {
//     Movement mvt;
//     mvt.start(-1, -1, 4, 4, 100);
//     while(mvt.poll()) {}
//     mvt.start(1, -1, 6, 6, 100);
//     while(mvt.poll()) {}
//     mvt.start(1, 1, 20, 20, 100);
//     while(mvt.poll()) {}

//     // TODO:
//     // 1. look for ewok (do this indefinitely, until we see it)
//     //   a. idea: do a rotation.  Log position and IR data for each reading.
//     //            look for a "bump" in IR data.  This might fix the issue
//     //            of looking for an ewok against a white background...
//     // 2. pick it up
//     // 3. go to edge
//     // 4. Drop it.
// }

// /**
//  * Starting from where the ewok was, start looking for an IR beacon signal.
//  * we HAVE to keep looking until we find it.
//  */
// void IRBeacon() {

//     ziplineLift.moveLift(Constants::frontLift, Constants::voltageIRFront);

//     Movement mvt;
//     mvt.start(1, -1, 3, 3, 100);
//     while(mvt.poll()) {}
//     bool foundIRBeacon = false;
//     while(true) {
//         mvt.start(-1, 1, 6, 6, 90);
//         while(mvt.poll()) {
//             float f10=0, f1=0;
//             for(int i=0;i<10;++i) {
//                 FFTPair fftPair = fft.sample();
//                 f10 += fftPair.highAmount;
//                 f1 += fftPair.lowAmount;
//             }
//             float totalAmount = sqrt(f10*f10 + f1*f1);
//             /*
//             if(totalAmount > Constants::FFT_THRESHOLD_TOTAL)
//             {
//                 foundIRBeacon = true;
//                 break;
//             }
//             */
//         }
//         if(foundIRBeacon) {
//             break;
//         }
//         mvt.start(1, -1, 6, 6, 90);
//         while(mvt.poll()) {}
//     }

//     motor.speed(Constants::MOTOR_LEFT, 0);
//     motor.speed(Constants::MOTOR_RIGHT, 0);

//     oled.clrScr();
//     oled.print("ir beacon found", 0, 0);
//     oled.update();





//     // TODO
//     // Set the lift to the correct height
//     // Move around until finding a large total IR signal
//     // (magnitude of (10k^2+1k^2)^.5 is large)
//     // Wait until 10k signal is > 10x 1k signal for 5 consecutive readings
// }

void prepareForBridge(Encoder& leftEnc, Encoder& rightEnc) {
    Movement mvt;
    mvt.move(1, -1, 6, 6, 100);
    mvt.move(1, 1, 6, 6, 100);
    mvt.move(1, -1, 10, 10, 100);
    bridge.dropBridge();
}

void mainRun() {
    //ziplineLift.liftFront();
    Menu m;
    m.run();
    Encoder leftEnc(Constants::LEFT_ENC_PIN);
    Encoder rightEnc(Constants::RIGHT_ENC_PIN);
    oled.invertText(false);

    initialLineFollow(leftEnc, rightEnc);

    delay(2000);

    handleFirstEwok(leftEnc, rightEnc);

    delay(2000);
    //
    // maneuverToDropLocation(leftEnc, rightEnc);

    // claw.deployBridge();

    // // we want to return to drop location so we go back onto the bridge
    // maneuverToBridge();

    // getToSecondEwok();

    // boolean gotSecondEwok = handleSecondEwok();

    // IRBeacon();

    // crossArch();

    // dropSecondEwok(gotSecondEwok);

    // handleThirdEwok();
}

void oneEwokRun() {
    // TODO
}
