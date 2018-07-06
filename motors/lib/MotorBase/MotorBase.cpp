#include "MotorBase.h"

MotorBase::MotorBase() {
    for(const auto& x : highPwmPins) {
        pinMode(x, OUTPUT);
    }
    for(const auto& x : lowPwmPins) {
        pinMode(x, OUTPUT);
    }
}
constexpr int8_t MotorBase::size() {
    return (sizeof highPwmPins);
}
void MotorBase::stop(const int8_t& motorNum) {
    analogWrite(highPwmPins[motorNum], 0);
    analogWrite(lowPwmPins[motorNum], 0);
}
void MotorBase::speed(const int8_t& motorNum, const int16_t& velocity) {
    if(velocity > 0) {
        if(velocity > 255){
            velocity = 255;
        }
        analogWrite(lowPwmPins[motorNum], 0);
        analogWrite(highPwmPins[motorNum], velocity);
    } else {
        if(velocity < -255){
            velocity = -255;
        }
        analogWrite(highPwmPins[motorNum], 0);
        analogWrite(lowPwmPins[motorNum], -velocity);
    }
}
