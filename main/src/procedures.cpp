#include "procedures.h"
#include <Arduino.h>
#include <Menu.h>
#include <LineFollower.h>
#include <Encoder.h>
#include <ClawBase.h>

void initialLineFollow(Encoder& leftEnc, Encoder& rightEnc) {
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
}

void mainRun() {
    Menu m;
    m.run();
    lineFollower.start();
    Encoder leftEnc(Constants::LEFT_ENC_PIN);
    Encoder rightEnc(Constants::RIGHT_ENC_PIN);
    oled.invertText(false);
    delay(500);

    initialLineFollow(leftEnc, rightEnc);
    // MANEUVER to EDGE

    claw.deployBridge();

}
