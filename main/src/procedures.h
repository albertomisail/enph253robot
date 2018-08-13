#pragma once
#include <Encoder.h>
#include <Constants.h>

void mainRun();
bool lookForEwok(int, int, int);
bool moveForwardToEwok(int, int);
void initialLineFollow(Encoder&, Encoder&);
void maneuverToDropLocation();
void handleFirstEwok(Encoder& leftEnc, Encoder& rightEnc);
void getToSecondEwok();
void handleSecondEwok();
void IRBeacon();
void maneuverToIR();
void maneuverToSecondDropLocation(Encoder&, Encoder&);
void handleThirdEwok();
void maneuverToSecondBridge();
void handleFourthEwok();