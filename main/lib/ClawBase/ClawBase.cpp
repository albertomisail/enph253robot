#include "ClawBase.h"

ClawBase::ClawBase(){
    //ClawBase::init();
}

void ClawBase::init(){
    //(ClawBase::arm).attach(Constants::CLAW_ARM_PIN);
    (ClawBase::arm).attach(Constants::CLAW_ARM_PIN);
    (ClawBase::arm).write(Constants::angleOut);
    (ClawBase::claw).attach(Constants::CLAW_PIN);
    (ClawBase::claw).write(Constants::angleClose);
    ClawBase::buttonSwitch = true;
    ClawBase::bridge = true;
}

void ClawBase::deployBridge(){
    ClawBase::bridge = false;
    ClawBase::buttonSwitch = false;
    claw.write(Constants::angleOpen);
    arm.write(Constants::angleIn);
    delay(1000);
    arm.write(Constants::angleOut);
    claw.write(Constants::angleClose);
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
void ClawBase::pickEwok(){
    int step = (Constants::angleClose - Constants::angleOpen) / 5;
    int step2 = (Constants::angleIn - Constants::angleOut) / 5;
    (ClawBase::arm).write(Constants::angleOut);
    (ClawBase::claw).write(Constants::angleOpen);
    //ziplineLift.dropClaw();
    while(!buttonSwitch || (ClawBase::claw).read() <= Constants::angleClose ){
        (ClawBase::claw).write((ClawBase::claw).read() - step);
        buttonSwitch = digitalRead(Constants::buttonSwitchPin);
    }
    if(buttonSwitch){
        while((ClawBase::arm).read() <= Constants::angleIn ){
            (ClawBase::arm).write((ClawBase::arm).read() + step);
        }
        (ClawBase::claw).write(Constants::angleOpen);
        delay(20);
        (ClawBase::arm).write(Constants::angleOut);
    } else{(ClawBase::claw).write(Constants::angleOpen);}
    //ziplineLift.liftClaw();
    ClawBase::buttonSwitch = false;
}

ClawBase claw;
