#pragma once
#include <Arduino.h>
#include <MyOLED.h>

constexpr uint8_t GO_BTN_PIN = PB10;
constexpr uint8_t POT_PIN = PB1;

class PIDScreen {
private:
	std::initializer_list<const char*> fields;
	void handleField(const int&);

public:
	int16_t[N] vals;
	constexpr PIDScreen(const std::initializer_list<const char*> init&);
	void begin(T);
	
};

extern PIDScreen pidScreen;
