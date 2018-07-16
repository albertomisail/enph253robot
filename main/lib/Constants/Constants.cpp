#include "Constants.h"


constexpr int8_t Constants::highPwmPins[];
constexpr int8_t Constants::lowPwmPins[];

MenuItem Constants::PROPORTIONAL("P", 0, 256, 40);
MenuItem Constants::INTEGRAL("I", 0, 20, 0);
MenuItem Constants::DERIVATIVE("D", 0, 40, 5);
MenuItem Constants::BASE_SPEED("BS", 0, 256, 150);
MenuItem Constants::LEFT_THRESHOLD("LT", 0, 4096, 1024);
MenuItem Constants::RIGHT_THRESHOLD("RT", 0, 4096, 1024);
