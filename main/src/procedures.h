#pragma once
#include <Encoder.h>

void mainRun();
void oneEwokRun();

void initialLineFollow(Encoder&, Encoder&);

void maneuverToDropLocation();

void handleFirstEwok(Encoder& leftEnc, Encoder& rightEnc);

void getToSecondEwok();

bool handleSecondEwok();

void crossArch();
