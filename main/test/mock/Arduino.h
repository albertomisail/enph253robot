#pragma once

#include "defines.h"
#include "ADC.h"
#include "Servo.h"

void delay(int32_t);
int32_t millis();
int32_t micros();
uint8_t digitalRead(uint8_t);
void digitalWrite(uint8_t, int16_t);
int16_t analogRead(uint8_t);
void analogWrite(uint8_t, int16_t);
void pinMode(uint8_t, uint8_t);

struct String {};
