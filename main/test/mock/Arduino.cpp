#include "Arduino.h"
namespace RobotTest {
	uint8_t digitalValue[40];
	int milliseconds = 0;
	void setDigitalValue(uint8_t pin, uint8_t value) {
		RobotTest::digitalValue[pin] = value;
	}
	void setMillis(int32_t val) {
		RobotTest::milliseconds = val;
	}
}

void delay(int32_t x) {
	RobotTest::milliseconds += x;
 // TODO
}
int32_t millis() {
    // TODO
	return RobotTest::milliseconds;
}
int32_t micros() {
    // TODO
}


uint8_t digitalRead(uint8_t pin) {
    // TODO
	return RobotTest::digitalValue[pin];
}
void digitalWrite(uint8_t, int16_t) {
    // TODO
}
int16_t analogRead(uint8_t) {
    // TODO
}
void analogWrite(uint8_t, int16_t) {
    // TODO
}



void pinMode(uint8_t, uint8_t) {
    // TODO
}
void interrupts() {
    // TODO
}
void noInterrupts() {
    // TODO
}
size_t strlen(char* s) {
	// TODO
	return -1;
}

