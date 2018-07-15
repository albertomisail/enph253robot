#include "ClawBase.h"

ClawBase::ClawBase(){
    ClawBase::init();
}

void ClawBase::init(){
    (ClawBase::arm).attach(clawArm);
    (ClawBase::arm).write(angleOut);
    (ClawBase::claw).attach(claw);
    (ClawBase::claw).write(angleClose);
    ClawBase::buttonSwitch = true;
    ClawBase::bridge = true;
}

void ClawBase::deployBridge(){
    ClawBase::bridge = false;
    ClawBase::buttonSwitch = false;
    (ClawBase::arm).write(angleOpen);
    delay(20);
    (ClawBase::arm).write(angleClose);
}

void ClawBase::pickEwok(){
    int step = (angleOpen - angleClose) / 5;
    (ClawBase::claw).write(angleOpen);
    //Lower arm
    while(!buttonSwitch || (ClawBase::claw).read() <= angleClose ){
        (ClawBase::claw).write((ClawBase::claw).read() - step);
        buttonSwitch = digitalRead(buttonSwitchPin);
    }
    if(buttonSwitch){
        (ClawBase::arm).write(angleIn);
        (ClawBase::claw).write(angleOpen);
        delay(20);
        (ClawBase::arm).write(angleOut);
    }else{(ClawBase::claw).write(angleOpen)}
    // add zipline arm
    ClawBase::buttonSwitch = false;
}

ClawBase claw;