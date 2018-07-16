#include "UltrasoundBase.h"

UltrasoundBase::UltrasoundBase() {
    init();
}
constexpr int8_t UltrasoundBase::size() {
    return (sizeof Constants::trigPins);
}
void UltrasoundBase::init() {
    for(int i = 0;i<size();++i) {
        distances[i] = 0;
        sensors[i].init(Constants::trigPins[i], Constants::echoPins[i]);
    }
}
unsigned short UltrasoundBase::measureDistance(const int8_t& sensor){
    unsigned short distance = sensors[sensor].readDisctanceInMm();
    UltrasoundBase::distances[sensor] = distance;
    return distance;
}

UltrasoundBase ultrasound;
