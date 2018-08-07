#include <iostream>
#include "PIDSpeed.h"

constexpr int16_t PIDSpeed::maxSpeed, PIDSpeed::minSpeed;

void PIDSpeed::start(int16_t baseSpeed_, int16_t timePerEncoder_) {
    start(baseSpeed_, timePerEncoder_, Encoder(Constants::LEFT_ENC_PIN), Encoder(Constants::RIGHT_ENC_PIN));
}
void PIDSpeed::start(int16_t baseSpeed_, int16_t timePerEncoder_, Encoder enc) {
    baseSpeed = baseSpeed_;
    timePerEncoder = timePerEncoder_;
    enc1 = enc;
    encoderCount = 1;
    enc1InitVal = enc1.getPosition();
    initValues();
}
void PIDSpeed::start(int16_t baseSpeed_, int16_t timePerEncoder_, Encoder encoder1, Encoder encoder2) {
    baseSpeed = baseSpeed_;
    timePerEncoder = timePerEncoder_;
    enc1 = encoder1;
    enc2 = encoder2;
    encoderCount = 2;
    enc1InitVal = enc1.getPosition();
    enc2InitVal = enc2.getPosition();
    initValues();
}
void PIDSpeed::initValues() {
    initTime = millis();
    error = 0;
    previousError = 0;
    counter = 0;
    ans = baseSpeed;
}
int32_t PIDSpeed::getEncoderVal() const {
    if(encoderCount < 2) {
        return enc1.getPosition()-enc1InitVal;
    }
    return (enc1.getPosition()-enc1InitVal+enc2.getPosition()-enc2InitVal)/2;
}
bool PIDSpeed::poll() {
    Encoder::poll();
    int32_t deltaT = millis()-lastTime;
    lastTime = millis();

    int32_t goalTime = timePerEncoder*getEncoderVal();
    int32_t error = millis()-goalTime;
    int32_t previousError = error;

    int32_t p = error*Constants::SPEED_P/1000;
    int32_t i = 0;
    if(error == previousError) {
        ++counter;
    } else {
        counter = 1;
    }
    int32_t d = (int32_t)Constants::DERIVATIVE.getVal() * (error-previousError) / (deltaT*counter) / 1000;
    ans = p+i+d+ baseSpeed;
    ans = min(maxSpeed, max(minSpeed, ans));
}
int16_t PIDSpeed::getSpeed() const {
    return ans;
}
