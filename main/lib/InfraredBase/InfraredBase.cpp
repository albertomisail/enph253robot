#include "InfraredBase.h"
#include "OLED_I2C.h"

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

void InfraredBase::performStartMeasurement() {
    base = analogRead(Constants::infraredReceiver);
    for(int i = 0; i < size(); i++){
        digitalWrite(Constants::infraredLeds[i], HIGH);
    }
    startTime = millis();
}

void InfraredBase::startMeasurement() {
    isMeasuring = true;
    digitalWrite(Constants::MULTIPLEXER_PIN, LOW);
}

bool InfraredBase::isDone() const {
    return !isMeasuring;
}

bool InfraredBase::poll() {
    if(!isMeasuring) return false;
    if(!started)
    {
        if(millis() < nextAvailable) return true;
        performStartMeasurement();
        started = true;
        return true;
    }
    if(millis() - startTime < Constants::ewokPulseDuration) return true;

    int16_t after = analogRead(Constants::infraredReceiver);
    for(int i = 0; i < size(); i++){
        digitalWrite(Constants::infraredLeds[i], LOW);
    }
    oled.clrScr();
    oled.printNumI(base - after, 0, 0);
    oled.update();
    lastResult = base-after;

    isMeasuring = false;
    started = false;
    nextAvailable = millis()+Constants::ewokPulseDuration;
    return false;
}

int InfraredBase::lastMeasurement() const {
    return lastResult;
}

/*
int InfraredBase::makeMeasurement(){
    delay(15);
    int after = analogRead(Constants::infraredReceiver);
    for(int i = 0; i < size(); i++){
        digitalWrite(Constants::infraredLeds[i], LOW);
    }
    oled.clrScr();
    oled.printNumI(base - after, 0, 0);
    oled.update();
    delay(15);
    return base - after;
} */

bool InfraredBase::objectDetected(int16_t infraredThreshold){
    return (lastMeasurement() >= infraredThreshold);
}

InfraredBase infrared;
