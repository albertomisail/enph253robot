#include "ZiplineLiftBase.h"

const uint8_t TBD_CONST = 0;
// TODO: Replace TBD_CONST with real values... They may all be different values

ZiplineLiftBase::ZiplineLiftBase(){
    ZiplineLiftBase::init();
}
void ZiplineLiftBase::init(){
    pinMode(Constants::potentiometerClaw, OUTPUT);
    pinMode(Constants::potentiometerOther, OUTPUT);
    ZiplineLiftBase::positionClawLift = TBD_CONST;
    ZiplineLiftBase::positionOtherLift = TBD_CONST;
    ZiplineLiftBase::liftClaw();
    ZiplineLiftBase::dropOther();
}
void ZiplineLiftBase::moveLift(const uint& numberOfMotor, const uint& position){
    if(numberOfMotor == Constants::clawLift){
        if(positionClawLift < position){
            // TODO: add threshold
            while((positionClawLift-position)*(positionClawLift-position) > TBD_CONST){
                motor.speed(numberOfMotor, Constants::speedLift);
                ZiplineLiftBase::positionClawLift = analogRead(Constants::potentiometerClaw);
            }
        }else{
            while((positionClawLift-position)*(positionClawLift-position) > TBD_CONST){
                motor.speed(numberOfMotor, -Constants::speedLift);
                ZiplineLiftBase::positionClawLift = analogRead(Constants::potentiometerClaw);
            }
        }
    }else{
       if(positionOtherLift < position){
            // TODO: add threshold
            while((positionOtherLift-position)*(positionOtherLift-position) > TBD_CONST){
                motor.speed(numberOfMotor, Constants::speedLift);
                ZiplineLiftBase::positionOtherLift = analogRead(Constants::potentiometerOther);
            }
        }else{
            while((positionOtherLift-position)*(positionOtherLift-position) > TBD_CONST){
                motor.speed(numberOfMotor, -Constants::speedLift);
                ZiplineLiftBase::positionOtherLift = analogRead(Constants::potentiometerOther);
            }
        }
    }
}
void ZiplineLiftBase::liftClaw(){
    ZiplineLiftBase::moveLift(Constants::clawLift, Constants::voltageUp);
}
void ZiplineLiftBase::dropClaw(){
    ZiplineLiftBase::moveLift(Constants::clawLift, Constants::voltageDown);
}
void ZiplineLiftBase::liftOther(){
    ZiplineLiftBase::moveLift(Constants::clawLift, Constants::voltageUp);
}
void ZiplineLiftBase::dropOther(){
    ZiplineLiftBase::moveLift(Constants::clawLift, Constants::voltageDown);
}

 ZiplineLiftBase ziplineLift;
