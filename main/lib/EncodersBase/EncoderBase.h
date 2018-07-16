#pragma once
#define ENCODER_DO_NOT_USE_INTERRUPTS
#include <Encoder.h>
// https://github.com/PaulStoffregen/Encoder/releases/tag/1.4.1
#include <Arduino.h>
#include <Constants.h>

class EncoderBase{
    private:
        long positions[sizeof leftEncoderPins];
        long positionsBefore[sizeof leftEncoderPins];
        Encoder encoders[sizeof leftEncoderPins];

    public:
        EncoderBase();
        void init();
        constexpr static int8_t size();
        long getPosition(const int8_t&);
        long getPositionChange(const int8_t&);
}

extern EncoderBase encoder;
