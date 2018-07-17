#include "Constants.h"

MenuItem Constants::PROPORTIONAL;
MenuItem Constants::INTEGRAL;
MenuItem Constants::DERIVATIVE;
MenuItem Constants::BASE_SPEED;
MenuItem Constants::LEFT_THRESHOLD;
MenuItem Constants::RIGHT_THRESHOLD;
MenuItem Constants::EDGE_THRESHOLD;

constexpr int8_t Constants::highPwmPins[];
constexpr int8_t Constants::lowPwmPins[];

void Constants::init() {
    /*
    PROPORTIONAL = MenuItem("P", 0, 256, 40);
    INTEGRAL = MenuItem("I", 0, 20, 0);
    DERIVATIVE = MenuItem("D", 0, 40, 5);
    BASE_SPEED = MenuItem("BS", 0, 256, 150);
    LEFT_THRESHOLD = MenuItem("LT", 0, 4096, 1024);
    RIGHT_THRESHOLD = MenuItem("RT", 0, 4096, 1024);
    */
    PROPORTIONAL = MenuItem("P", 0, 256, 35);
    INTEGRAL = MenuItem("I", 0, 20, 0);
    DERIVATIVE = MenuItem("D", 0, 40, 8);
    BASE_SPEED = MenuItem("BS", 0, 256, 150);
    LEFT_THRESHOLD = MenuItem("LT", 0, 4096, 2000);
    RIGHT_THRESHOLD = MenuItem("RT", 0, 4096, 2000);
    EDGE_THRESHOLD = MenuItem("ET", 0, 4096, 2000);
}
