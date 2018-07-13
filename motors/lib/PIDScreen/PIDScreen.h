#pragma once
#include <Arduino.h>
#include <MyOLED.h>
#include <utility>

constexpr uint8_t GO_BTN_PIN = PB13;
constexpr uint8_t POT_PIN = PB0;

template <int N>
class PIDScreen {
private:
	const std::initializer_list<const char*> fields;
	void handleField(const int&);

public:
	int16_t vals[N];
	constexpr PIDScreen(const std::initializer_list<const char*>&);
	void begin();

};

#include <PIDScreen.h>

template <int N>
constexpr PIDScreen<N>::PIDScreen(const std::initializer_list<const char*>& init) : fields(init) {
	//static_assert(std::tuple_size<decltype(init)>::value == N);
}

template <int N>
void PIDScreen<N>::begin() {
	pinMode(GO_BTN_PIN, INPUT);
	pinMode(POT_PIN, INPUT);

	int i = 0;
	for(const auto& f: fields) {
		oled.print(f, 0, i*10);
		oled.printNumI(0, 21, i*10, 4);
		++i;
	}
	for(int i=0;i<static_cast<int>(fields.size());++i) {
		handleField(i);
	}
}

template <int N>
void PIDScreen<N>::handleField(const int& index) {
	int32_t start = millis();
	int16_t mask = 0;
	bool hasBeenZero = false;
	//oled.invert(true);
	while(true) {
		int32_t now = millis();
		int16_t currentValue = analogRead(POT_PIN);
		int16_t motorSpeed = (currentValue>>4);

		if(now - start > 20) {
			uint8_t buttonValue = digitalRead(GO_BTN_PIN);
			mask <<= 1;
			mask |= (buttonValue == HIGH);
			if( (mask&255) == 0) {
				hasBeenZero = true;
			}
			if((mask&255) == 255 && hasBeenZero) {
				vals[index] =  motorSpeed;
				oled.invertText(false);
				oled.printNumI(motorSpeed, 21, index*10, 4);
				oled.update();
				return;
			}
		}
		oled.invertText(true);
		oled.printNumI(motorSpeed, 21, index*10, 4);

		/*
		for(int i=7;i>=0;--i)
		{
			oled.print(((mask & (1<<i)) ? "1" : "0"), (7-i)*7, 40);
		}
		oled.printNumI(hasBeenZero, 60, 40);
		oled.printNumI(start, 0, 50);
		oled.printNumI(now, 50, 50); */

		oled.update();
	}
}

extern PIDScreen<7> pidScreen({"P: ", "I: ", "D: ", "BS:", "L: ", "R: ", "E: "});
//extern PIDScreen<1> pidScreen({"BS:"});
