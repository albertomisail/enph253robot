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
constexpr uint8_t Constants::LEFT_ENC_PIN;
constexpr uint8_t Constants::RIGHT_ENC_PIN;
constexpr int8_t Constants::infraredLeds[];
constexpr int8_t Constants::infraredReceiver;
constexpr uint8_t Constants::MOTOR_LEFT, Constants::MOTOR_RIGHT;

void Constants::init() {
    PROPORTIONAL = MenuItem("P", 0, 256, 24);
    INTEGRAL = MenuItem("I", 0, 20, 0);
    DERIVATIVE = MenuItem("D", 0, 40, 4);
    BASE_SPEED = MenuItem("BS", 0, 256, 130);
    LEFT_THRESHOLD = MenuItem("LT", 0, 4096, 3100);
    RIGHT_THRESHOLD = MenuItem("RT", 0, 4096, 3100);
    EDGE_THRESHOLD = MenuItem("ET", 0, 4096, 1500);
}
