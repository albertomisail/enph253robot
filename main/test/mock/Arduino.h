#pragma once

#include "defines.h"
#include "ADC.h"
#include "Servo.h"
#include "gtest/gtest.h"

namespace RobotTest {
	void setDigitalValue(uint8_t, uint8_t);
	void setMillis(int32_t);
};

void delay(int32_t);
int32_t millis();
int32_t micros();
uint8_t digitalRead(uint8_t);
void digitalWrite(uint8_t, int16_t);
int16_t analogRead(uint8_t);
void analogWrite(uint8_t, int16_t);
void pinMode(uint8_t, uint8_t);
void interrupts();
void noInterrupts();
size_t strlen(char* s);

template<typename T, typename U>
T min(const T& x, const U& y) {
    return (x < y ? x : static_cast<T>(y));
}
template<typename T, typename U>
T max(const T& x, const U& y) {
    return (x > y ? x : static_cast<T>(y));
}
