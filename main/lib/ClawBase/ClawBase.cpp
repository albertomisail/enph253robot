#include "ClawBase.h"
#include "OLED_I2C.h"
ClawBase::ClawBase(){
    //ClawBase::init();
}

void ClawBase::init(){
    //(ClawBase::arm).attach(Constants::CLAW_ARM_PIN);
    (ClawBase::arm).attach(Constants::CLAW_ARM_PIN);
    (ClawBase::arm).write(Constants::angleInit);
    (ClawBase::claw).attach(Constants::CLAW_PIN);
    //(ClawBase::claw).write(Constants::angleClose);
    (ClawBase::claw).write(Constants::angleOpen);
    ClawBase::buttonSwitch = true;
    ClawBase::bridge = true;
    pinMode(Constants::buttonSwitchPin, INPUT);
}

void ClawBase::deployBridge(){
    ClawBase::bridge = false;
    ClawBase::buttonSwitch = false;
    int step = 5;
    while((ClawBase::arm).read() > Constants::angleOut){
        (ClawBase::arm).write((ClawBase::arm).read() - step);
        delay(250);
    }
    delay(1000);
    claw.write(Constants::angleOpen);
    delay(1000);
    // arm.write(Constants::angleIn);
    // delay(1000);
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
bool ClawBase::pickEwok(){
    int step = (Constants::angleClose - Constants::angleOpen) / Constants::numSteps;
    int step2 = (Constants::angleIn - Constants::angleOut) / Constants::numSteps;
    ClawBase::buttonSwitch = false;

    (ClawBase::claw).write(Constants::angleOpen);
    delay(250);

    Serial.println("here");

    int step_dir = Constants::angleOut-arm.read();
    step_dir = step_dir/abs(step_dir);
    for(int i=arm.read();abs(arm.read()-Constants::angleOut) > 0;i += step_dir)
    {
        arm.write(i);
        delay(10);
    }

    //ziplineLift.dropFront();
    while(!buttonSwitch && (ClawBase::claw).read() < Constants::angleClose){
        (ClawBase::claw).write((ClawBase::claw).read() + step);
        delay(125);
        buttonSwitch = digitalRead(Constants::buttonSwitchPin);
        oled.clrScr();
        oled.printNumI((ClawBase::claw).read(), 0, 0);
        oled.printNumI(buttonSwitch, 0, 10);
        oled.update();
    }
    delay(250);
    Serial.println("here2");
    delay(250);
    boolean result = false;
    //if(buttonSwitch) {
        // while((ClawBase::arm).read() < Constants::angleIn) {
        //     (ClawBase::arm).write((ClawBase::arm).read() + step2);
        //     delay(250);
        // }
        //(ClawBase::arm).write(Constants::angleIn);
        //result = true;
        //(ClawBase::claw).write(Constants::angleOpen);
    //} else {
        //(ClawBase::claw).write(Constants::angleOpen);
        //arm.write(Constants::angleIn);
    //}
    //ziplineLift.liftFront();
    (ClawBase::arm).write(Constants::angleClose);
    arm.write(Constants::angleIn);
    return result;
}

void ClawBase::dropEwok() {
    (ClawBase::claw).write(Constants::angleOpen);
    delay(500);
}

ClawBase claw;
