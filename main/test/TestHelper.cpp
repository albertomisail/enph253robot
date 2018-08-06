#include "TestHelper.h"

namespace RobotTest {
	void mockEncoderSteps(uint8_t pin, int steps, int startTime) {
		RobotTest::setMillis(startTime);
		for(int i=0;i<steps;++i) {
			RobotTest::setDigitalValue(pin, LOW);
			delay(10);
			Encoder::poll();
			RobotTest::setDigitalValue(pin, HIGH);
			delay(10);
			Encoder::poll();
		}
	}
};
