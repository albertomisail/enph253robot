#pragma once
#include <Arduino.h>
#include <Servo.h>
#include <Constants.h>

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
    void startPickEwok();
    void finishPickEwok();
    bool pickEwok();
    void dropEwok();
};

extern ClawBase claw;
