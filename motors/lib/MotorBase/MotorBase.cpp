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
    speeds[motorNum] = 0;
}
void MotorBase::speed(const int8_t& motorNum, int16_t velocity) {
    if(speeds[motorNum] != 0
    && (speeds[motorNum] > 0) != (velocity > 0)
    && velocity != 0) {
        // If we're switching directions, then set to zero first.
        analogWrite(lowPwmPins[0], 0);
        analogWrite(highPwmPins[0], 0);
        speeds[motorNum] = 0;
        delay(10);
    }
    int8_t zeroPin, nonzeroPin;
    if(velocity > 0) {
        if(velocity > 255){
            velocity = 255;
        }
        zeroPin = lowPwmPins[motorNum];
        nonzeroPin = highPwmPins[motorNum];
    } else {
        if(velocity < -255){
            velocity = -255;
        }
        zeroPin = highPwmPins[motorNum];
        nonzeroPin = lowPwmPins[motorNum];
    }
    analogWrite(zeroPin, 0);
    for(int i=abs(speeds[motorNum]); i<abs(velocity); i += 10)
    {
        analogWrite(nonzeroPin, i);
        delay(10);
    }
    analogWrite(nonzeroPin, abs(velocity));
    speeds[motorNum] = velocity;
}

MotorBase motor;
