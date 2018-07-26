#pragma once
#include <Encoder.h>

void mainRun();
void oneEwokRun();

bool lookForEwok(int, int, int, int);
bool moveForwardToEwok(int, int);
void initialLineFollow(Encoder&, Encoder&);

void maneuverToDropLocation();

void handleFirstEwok(Encoder& leftEnc, Encoder& rightEnc);

void getToSecondEwok();

bool handleSecondEwok();

void crossArch();
