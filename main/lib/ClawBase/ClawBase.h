#pragma once
#include <Arduino.h>
#include <Servo.h>
#include <Constants.h>
#include <ZiplineLiftBase.h>

class ClawBase{
private:
    Servo arm;
    Servo claw;
    bool buttonSwitch;
    bool bridge;

public:
    ClawBase();
    void init();
    void deployBridge();
    bool pickEwok();
    void dropEwok();
};

extern ClawBase claw;
