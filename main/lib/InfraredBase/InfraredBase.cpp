#include "InfraredBase.h"

InfraredBase::InfraredBase(){
    InfraredBase::init();
}
void InfraredBase::init(){
    for(int i = 0; i < InfraredBase::size(); i++){
        pinMode(Constants::infraredLeds[i], OUTPUT);
    }
    pinMode(Constants::infraredReceiver, INPUT);
}
constexpr int8_t InfraredBase::size(){
    return sizeof Constants::infraredLeds;
}
int InfraredBase::makeMeasurement(){
    int base = analogRead(Constants::infraredReceiver);
    for(int i = 0; i < size(); i++){
        digitalWrite(Constants::infraredLeds[i], HIGH);
    }
    delay(50);
    for(int i = 0; i < size(); i++){
        digitalWrite(Constants::infraredLeds[i], LOW);
    }
    int after = analogRead(Constants::infraredReceiver);
    return after - base;
}
bool InfraredBase::objectDetected(){
    if(Constants::infraredThreshold > makeMeasurement()){
        return false;
    }else{
        return true;
    }
}

InfraredBase infrared;
