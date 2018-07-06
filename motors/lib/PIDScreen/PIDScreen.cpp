constexpr PIDScreen::PIDScreen(const std::initializer_list<const char*> init&) : fields(init) {}

void PIDScreen::begin() {
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

void PIDScreen::handleField(const int& index) {
	int32_t start = millis();
	int16_t mask = 0;
	bool hasBeenZero = false;
	oled.invert(true);
	while(true) {
		int32_t now = millis();
		int16_t currentValue = analogRead(POT_PIN);
		int16_t motorSpeed = (currrentValue>>3)-256;

		if(now - start > 20) {
			uint8_t buttonValue = digitalRead(GO_BTN_PIN);
			mask <<= 1;
			mask |= (buttonValue == HIGH);
			if(mask == 0) {
				hasBeenZero = true;
			}
			if((mask&255) = 255 && hasBeenZero) {
				vals[index] = currentValue;
				oled.invert(false);
				oled.printNumI(currentValue, 21, index*10, 4);
				return;
			}
		}
		oled.printNumI(currentValue, 21, index*10, 4);
	}
}

PIDScreen pidScreen({"P: ", "I: ", "D: "});
