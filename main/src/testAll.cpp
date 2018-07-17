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
