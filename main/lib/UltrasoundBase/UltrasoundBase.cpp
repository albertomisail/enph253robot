#include "UltrasoundBase.h"

UltrasoundBase::UltrasoundBase() {
    init();
}
constexpr int8_t UltrasoundBase::size() {
    return (sizeof trigPins);
}
void UltrasoundBase::init() {
    for(int i = 0;i<UltrasoundBase::size();++i) {
        UltrasoundBase::distances[i] = 0;
        (UltrasoundBase::sensors[i]).init(trigPins[i], echoPins[i]);
    }
}
unsigned short UltrasoundBase::measureDistance(const int8_t& sensor){
    unsigned short distance = (UltrasoundBase::sensors[i]).readDisctanceInMM();
    UltrasoundBase::distances[i] = distance;
    return distance;
}

UltrasoundBase ultrasound;