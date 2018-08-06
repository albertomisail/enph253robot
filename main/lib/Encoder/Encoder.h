#pragma once
#define ENCODER_DO_NOT_USE_INTERRUPTS
#include <Arduino.h>
#include <Constants.h>

// Currently, this does not handle direction.
class Encoder {
public:
    constexpr static uint8_t MAX_ENCODERS = 4;
private:
    static int8_t encoderPins[MAX_ENCODERS];
    static int8_t encoderPinCnt[MAX_ENCODERS];
    static int16_t distances[MAX_ENCODERS];
    static int8_t lastState[MAX_ENCODERS];
    static uint8_t pinCount;
    static uint32_t lastPoll;
    int8_t ind = 0;
public:
    Encoder(const uint8_t& pin);
    ~Encoder();
    static void poll();
    //void init();
    //constexpr static int8_t size();
    int16_t getPosition() const;
    void reset();
    //long getPositionChange(const int8_t&);
};

//extern EncoderBase encoder;
