#include "MotorBase.h"

MotorBase::MotorBase() {
    init();
}
constexpr int8_t MotorBase::size() {
    return (sizeof highPwmPins);
}
void MotorBase::init() {
    for(const auto& x : highPwmPins) {
        pinMode(x, OUTPUT);
        analogWrite(x, 0);
    }
    // adding the delay, seeting to output a pin does one cycle of the pwm
    // if both pins are set to output at the same time then the MOSFETS short
    delay(20);
    for(const auto& x : lowPwmPins) {
        pinMode(x, OUTPUT);
        analogWrite(x, 0);
    }
    for(int i = 0;i<sizeof highPwmPins;++i) {
        speeds[i] = 0;
    }
}
void MotorBase::speed(const int8_t& motorNum, int16_t velocity) {
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
void MotorBase::stop(const int8_t& motorNum) {
    MotorBase::speed(motorNum, 0);
    speeds[motorNum] = 0;
}
void MotorBase::shut_dowm(){
    for(int8_t i = 0; i < MotorBase::size(); i++){
        MotorBase::stop(i);
    }
}

MotorBase motor;