#include "Arduino.h"
namespace RobotTest {
	uint8_t digitalValue[40];
	uint8_t pinModeValue[40];
	int milliseconds = 0;
	int16_t analogValue[40];
	void setDigitalValue(uint8_t pin, uint8_t value) {
		RobotTest::digitalValue[pin] = value;
	}
	void setAnalogValue(uint8_t pin, int16_t value) {
		RobotTest::analogValue[pin] = value;
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
	return RobotTest::milliseconds;
}
int32_t micros() {
    // TODO
}


uint8_t digitalRead(uint8_t pin) {
    // TODO
	ASSERT_EQ(INPUT, RobotTest::pinModeValue[pin]);
	return RobotTest::digitalValue[pin];
}
void digitalWrite(uint8_t pin, int16_t val) {
	ASSERT_EQ(OUTPUT, RobotTest::pinModeValue[pin]);
	RobotTest::digitalValue[pin] = val;
}
int16_t analogRead(uint8_t pin) {
	ASSERT_EQ(INPUT, RobotTest::pinModeValue[pin]);
	RobotTest::analogValue[pin] = val;
}
void analogWrite(uint8_t pin, int16_t val) {
	ASSERT_EQ(OUTPUT, RobotTest::pinModeValue[pin]);
	RobotTest::analogValue[pin] = val;
}



void pinMode(uint8_t pin, uint8_t mode) {
	RobotTest::pinModeValue[pin] = mode;
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

