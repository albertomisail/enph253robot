#include "ZiplineLiftBase.h"

ZiplineLiftBase::ZiplineLiftBase(){
    ZiplineLiftBase::init();
}
void ZiplineLiftBase::init(){
    pinMode(potentiometerClaw, OUTPUT);
    pinMode(potentiometerOther, OUTPUT);
    ZiplineLiftBase::positionClawLift = ;
    ZiplineLiftBase::positionOtherLift = ;
    ZiplineLiftBase::liftClaw();
    ZiplineLiftBase::dropOther();
}
void ZiplineLiftBase::moveLift(const uint& numberOfMotor, const uint& position){
    if(numberOfMotor == clawLift){
        if(positionClawLift < position){
            // TODO: add threshold
            while((positionClawLift-position)*(positionClawLift-position) > ){
                motor.speed(numberOfMotor, speedLift);
                ZiplineLiftBase::positionClawLift = analogRead(potentiometerClaw);
            }
        }else{
            while((positionClawLift-position)*(positionClawLift-position) > ){
                motor.speed(numberOfMotor, -speedLift);
                ZiplineLiftBase::positionClawLift = analogRead(potentiometerClaw);
            }
        }
    }else{
       if(positionOtherLift < position){
            // TODO: add threshold
            while((positionOtherLift-position)*(positionOtherLift-position) > ){
                motor.speed(numberOfMotor, speedLift);
                ZiplineLiftBase::positionOtherLift = analogRead(potentiometerOther);
            }
        }else{
            while((positionOtherLift-position)*(positionOtherLift-position) > ){
                motor.speed(numberOfMotor, -speedLift);
                ZiplineLiftBase::positionOtherLift = analogRead(potentiometerOther);
            }
        } 
    }
}
void ZiplineLiftBase::liftClaw(){
    ZiplineLiftBase::moveLift(clawLift, voltageUp);
}
void ZiplineLiftBase::dropClaw(){
    ZiplineLiftBase::moveLift(clawLift, voltageDown);
}
void ZiplineLiftBase::liftOther(){
    ZiplineLiftBase::moveLift(clawLift, voltageUp);
}
void ZiplineLiftBase::dropOther(){
    ZiplineLiftBase::moveLift(clawLift, voltageDown);
}

 ZiplineLiftBase ziplineLift;