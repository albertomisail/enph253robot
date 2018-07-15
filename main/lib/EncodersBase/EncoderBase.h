#pragma once
#include <Encoder.h>
// https://github.com/PaulStoffregen/Encoder/releases/tag/1.4.1
#include <Arduino.h>
#include <constants.h>

class EncoderBase{
    private:
        long positions[sizeof leftEncoderPins];
        Encoder encoders[sizeof leftEncoderPins];

    public:
        EncoderBase();
        void init();
        constexpr static int8_t size();
        long getPosition(const int8_t&);
}

extern EncoderBase encoder;