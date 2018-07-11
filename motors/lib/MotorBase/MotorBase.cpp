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
    for(const auto& x : lowPwmPins) {
        pinMode(x, OUTPUT);
        analogWrite(x, 0);
    }
    for(int i = 0;i<sizeof highPwmPins;++i) {
        speeds[i] = 0;
    }
}
void MotorBase::stop(const int8_t& motorNum) {
    analogWrite(highPwmPins[motorNum], 0);
    analogWrite(lowPwmPins[motorNum], 0);
    speeds[motorNum] = 0;
}
int printColumn = 0;
void myAnalogReadClear() {
    printColumn = 0;
}
void analogWriteLog(int pin, int val)
{
    //oled.printNumI(pin, 0, printColumn*10);
    //oled.printNumI(val, 30, printColumn*10);
    analogWrite(pin, val);
    //printColumn++;
}
void MotorBase::speed(const int8_t& motorNum, int16_t velocity) {
    printColumn = 0;
    //oled.clrScr();
    if(velocity > 0) {
        if(velocity > 255){
            velocity = 255;
        }
        analogWriteLog(lowPwmPins[motorNum], 0);
        analogWriteLog(highPwmPins[motorNum], velocity);
    } else {
        if(velocity < -255){
            velocity = -255;
        }
        analogWriteLog(highPwmPins[motorNum], 0);
        analogWriteLog(lowPwmPins[motorNum], -velocity);
    }
    oled.update();
    /*
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
    for(int16_t i=abs(speeds[motorNum]); i<abs(velocity); i += 1)
    {
        analogWrite(nonzeroPin, i);
        delay(10);
    }
    analogWrite(nonzeroPin, abs(velocity));
    speeds[motorNum] = velocity; */
}

MotorBase motor;
