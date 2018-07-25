#pragma once
#include <Arduino.h>
#include <MotorBase.h>
#include <Constants.h>

class ZiplineLiftBase{
    private:
        uint16_t positionFrontLift;
        uint16_t positionBackLift;

    public:
        ZiplineLiftBase();
        void init();
        void moveLift(const uint8_t& motorPin, const uint16_t& position);
        void liftFront();
        void dropFront();
        void liftBack();
        void dropBack();
};

extern ZiplineLiftBase ziplineLift;
