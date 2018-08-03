#pragma once
#include <Encoder.h>
#include <Constants.h>

void mainRun();
void oneEwokRun();

bool lookForEwok(int, int, int, int, int);
bool moveForwardToEwok(int, int);
void initialLineFollow(Encoder&, Encoder&);

void maneuverToDropLocation();

bool handleFirstEwok(Encoder& leftEnc, Encoder& rightEnc);

void getToSecondEwok();

void handleSecondEwok();

void IRBeacon();
void maneuverToIR();
void maneuverToSecondDropLocation(Encoder&, Encoder&);
void handleThirdEwok();