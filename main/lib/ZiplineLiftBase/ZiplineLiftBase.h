#pragma once
#include <Arduino.h>
#include <MotorBase.h>
#include <Constants.h>

class ZiplineLiftBase{
    private:
        uint8_t positionClawLift;
        uint8_t positionOtherLift;

    public:
        ZiplineLiftBase();
        void init();
        void moveLift(const uint& numberOfMotor, const uint& position);
        void liftClaw();
        void dropClaw();
        void liftOther();
        void dropOther();
}

extern ZiplineLiftBase ziplineLift;