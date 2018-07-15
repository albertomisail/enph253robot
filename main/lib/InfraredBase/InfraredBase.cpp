#include "InfraredBase.h"

InfraredBase::InfraredBase(){
    InfraredBase::init();
}
void InfraredBase::init(){
    for(int i = 0; i < InfraredBase::size(); i++){
        pinMode(infraredLeds[i], OUTPUT);
    }
    pinMode(infraredReceiver, INPUT);
}
constexpr static int8_t InfraredBase::size(){
    return sizeof infraredLeds;
}
int InfraredBase::makeMeasurement(){
    int base = analogRead(infraredReceiver);
    for(int i = 0; i < InfraredBase::size(); i++){
        digitalWrite(infraredLeds[i], HIGH);
    }
    delay(50);
    for(int i = 0; i < InfraredBase::size(); i++){
        digitalWrite(infraredLeds[i], LOW);
    }
    int after = analogRead(infraredReceiver);
    return after - base;
}
bool InfraredBase::objectDetected(){
    if(infraredThreshold > InfraredBase::makeMeasurement){
        return false;
    }else{
        return true;
    }
}

InfraredBase infrared;