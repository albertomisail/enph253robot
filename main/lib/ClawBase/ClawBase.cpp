#include "ClawBase.h"
#include "OLED_I2C.h"
ClawBase::ClawBase(){
}

void ClawBase::init(){
    (ClawBase::arm).attach(Constants::CLAW_ARM_PIN);
    (ClawBase::arm).write(Constants::angleIn);
    (ClawBase::claw).attach(Constants::CLAW_PIN);
    (ClawBase::claw).write(Constants::angleClose);
}

void ClawBase::startPickEwok() {
    (ClawBase::claw).write(Constants::angleOpen);
    delay(500);

    int step_dir = Constants::angleOut-arm.read();
    step_dir = step_dir/abs(step_dir);
    for(int i=arm.read();abs(arm.read()-Constants::angleOut) > 0;i += step_dir)
    {
        arm.write(i);
        delay(5);
    }
}

void ClawBase::finishPickEwok(){
    int step = (Constants::angleClose - Constants::angleOpen) / Constants::numSteps;
    int step2 = (Constants::angleOut - Constants::angleIn) / Constants::numSteps;
    while((ClawBase::claw).read() < Constants::angleClose){
        (ClawBase::claw).write((ClawBase::claw).read() + step);
        delay(40);
    }
    delay(250);
    while((ClawBase::arm).read() < Constants::angleIn) {
        (ClawBase::arm).write((ClawBase::arm).read() + step2);
        delay(100);
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
    delay(750);
    (ClawBase::claw).write(Constants::angleDrop);
    delay(1000);
    arm.write(Constants::angleIn);
    delay(500);
    claw.write(Constants::angleClose);
}

ClawBase claw;
