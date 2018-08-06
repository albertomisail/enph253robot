#include "ClawBase.h"
#include "OLED_I2C.h"
ClawBase::ClawBase(){
    //ClawBase::init();
}

void ClawBase::init(){
    (ClawBase::arm).attach(Constants::CLAW_ARM_PIN);
    (ClawBase::arm).write(Constants::angleIn);
    (ClawBase::claw).attach(Constants::CLAW_PIN);
    (ClawBase::claw).write(Constants::angleClose);
    ClawBase::buttonSwitch = true;
    ClawBase::bridge = true;
    pinMode(Constants::buttonSwitchPin, INPUT);
}

void ClawBase::startPickEwok() {

    (ClawBase::claw).write(Constants::angleOpen);
    delay(500);

    int step_dir = Constants::angleOut-arm.read();
    step_dir = step_dir/abs(step_dir);
    for(int i=arm.read();abs(arm.read()-Constants::angleOut) > 0;i += step_dir)
    {
        arm.write(i);
        delay(20);
    }
}

void ClawBase::finishPickEwok(){

    int step = (Constants::angleClose - Constants::angleOpen) / Constants::numSteps;
    int step2 = (Constants::angleOut - Constants::angleIn) / Constants::numSteps;
    while((ClawBase::claw).read() < Constants::angleClose){
        (ClawBase::claw).write((ClawBase::claw).read() + step);
        delay(70);
    }
    delay(250);
    while((ClawBase::arm).read() < Constants::angleIn) {
        (ClawBase::arm).write((ClawBase::arm).read() + step2);
        delay(140);
    }
    (ClawBase::arm).write(Constants::angleIn);
    delay(500);
}

bool ClawBase::pickEwok() {
    startPickEwok();
    finishPickEwok();
    return true;
}

void ClawBase::dropEwok() {
    arm.write(Constants::angleOut);
    delay(500);
    (ClawBase::claw).write(Constants::angleDrop);
    delay(1000);
    arm.write(Constants::angleIn);
    delay(500);
    claw.write(Constants::angleClose);
}

ClawBase claw;
