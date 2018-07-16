#include "Encoder.h"

uint8_t Encoder::pinCount = 0;
int8_t Encoder::encoderPins[Encoder::MAX_ENCODERS] = {-1};
int8_t Encoder::lastState[Encoder::MAX_ENCODERS] = {-1};
int8_t Encoder::encoderPinCnt[Encoder::MAX_ENCODERS] = {0};
int16_t Encoder::distances[Encoder::MAX_ENCODERS] = {0};
uint32_t Encoder::lastPoll = 0;

Encoder::Encoder(const uint8_t& pin) {
    ind = -1;
    for(int i=0;i<MAX_ENCODERS;++i)
    {
        if(encoderPins[i] == -1 && ind == -1)
        {
            ind = i;
        }
        if(encoderPins[i] == pin)
        {
            ind = i;
            break;
        }
    }
    encoderPins[ind] = pin;
    encoderPinCnt[ind]++;
}

Encoder::~Encoder() {
    if(!(--encoderPinCnt[ind])) {
        encoderPins[ind] = -1;
        lastState[ind] = -1;
    }
}

void Encoder::poll() {
    int v = 0;
    int32_t t = millis();
    if(t - lastPoll < Constants::ENCODER_POLL_TIME)
    {
        return;
    }
    lastPoll = t;
    for(int i=0;i<MAX_ENCODERS;++i)
    {
        if(encoderPins[i] == -1) continue;
        if((v=digitalRead(encoderPins[i])) == 1 && lastState[i] == 0)
        {
            ++distances[i];
        }
        lastState[i] = v;
    }
}

int16_t Encoder::getPosition() const {
    poll();
    return distances[ind];
}
