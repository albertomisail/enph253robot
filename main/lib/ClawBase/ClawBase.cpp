#include "ClawBase.h"

ClawBase::ClawBase(){
    //ClawBase::init();
}

void ClawBase::init(){
    (ClawBase::arm).attach(Constants::clawArm);
    (ClawBase::arm).write(Constants::angleOut);
    (ClawBase::claw).attach(Constants::CLAW_PIN);
    (ClawBase::claw).write(Constants::angleClose);
    ClawBase::buttonSwitch = true;
    ClawBase::bridge = true;
}

void ClawBase::deployBridge(){
    ClawBase::bridge = false;
    ClawBase::buttonSwitch = false;
    //claw.write(Constants::angleOpen);
    arm.write(Constants::angleOut);
    delay(1000);
    arm.write(Constants::angleIn);
    //claw.write(Constants::angleClose);
}

/*
TODO: fix pickEwok
void ClawBase::pickEwok(){
    int step = (Constants::angleOpen - Constants::angleClose) / 5;
    (ClawBase::claw).write(Constants::angleOpen);
    //ziplineLift.dropClaw();
    while(!buttonSwitch || (ClawBase::claw).read() <= Constants::angleClose ){
        (ClawBase::claw).write((ClawBase::claw).read() - step);
        buttonSwitch = digitalRead(Constants::buttonSwitchPin);
    }
    if(buttonSwitch){
        (ClawBase::arm).write(Constants::angleIn);
        (ClawBase::claw).write(Constants::angleOpen);
        delay(20);
        (ClawBase::arm).write(Constants::angleOut);
    } else{(ClawBase::claw).write(Constants::angleOpen);}
    //ziplineLift.liftClaw();
    ClawBase::buttonSwitch = false;
}
*/

ClawBase claw;
