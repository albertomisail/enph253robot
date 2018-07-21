#include "ZiplineLiftBase.h"
#include "OLED_I2C.h"

const uint16_t ERR_THR = 50;
// TODO: Replace ERR_THR with real values... They may all be different values

ZiplineLiftBase::ZiplineLiftBase(){
    ZiplineLiftBase::init();
}
void ZiplineLiftBase::init(){
    pinMode(Constants::potFront, INPUT);
    pinMode(Constants::potBack, INPUT);
    pinMode(Constants::frontLift, OUTPUT);
    pinMode(Constants::backLift, OUTPUT);
    ZiplineLiftBase::positionFrontLift = analogRead(Constants::potFront);
    ZiplineLiftBase::positionBackLift = analogRead(Constants::potBack);
    //ZiplineLiftBase::liftFront();
    //ZiplineLiftBase::dropFront();
}
void ZiplineLiftBase::moveLift(const uint8_t& motorPin, const uint16_t& position){
    if(motorPin == Constants::frontLift){
        //Higher voltage doesnt necessarily mean the position is up and also Hbridge might be hooked up backwards
        if (ZiplineLiftBase::positionFrontLift <= Constants::voltageUpFront || ZiplineLiftBase::positionFrontLift >= Constants::voltageDownFront) {
            if(positionFrontLift < position){
                // TODO: add threshold
                // Might have to be careful with the squaring. If the difference is larger than 256 it will overflow 16 bit.
                for(int32_t i =0; abs(positionFrontLift-position) > ERR_THR; ++i){
                    motor.speed(motorPin, Constants::speedLift);
                    ZiplineLiftBase::positionFrontLift = analogRead(Constants::potFront);
                    if (i%100 == 0) {
                        oled.clrScr();
                        oled.printNumI(positionFrontLift, 0, 0);
                        oled.update();
                    }
                }
                motor.speed(motorPin, 0);
            }else{
                for(int32_t i=0; abs(positionFrontLift-position) > ERR_THR; ++i){
                    motor.speed(motorPin, -Constants::speedLift);
                    ZiplineLiftBase::positionFrontLift = analogRead(Constants::potFront);
                    if(i%100 == 0) {
                        oled.clrScr();
                        oled.printNumI(positionFrontLift, 0, 0);
                        oled.update();
                    }
                }
                motor.speed(motorPin, 0);
            }
        }
    }else{
        if (ZiplineLiftBase::positionBackLift <= Constants::voltageUpBack || ZiplineLiftBase::positionBackLift >= Constants::voltageDownBack) {
            if(positionBackLift < position){
                // TODO: add threshold
                while(abs(positionBackLift-position) > ERR_THR){
                    motor.speed(motorPin, Constants::speedLift);
                    ZiplineLiftBase::positionBackLift = analogRead(Constants::potBack);
                }
            }else{
                while(abs(positionBackLift-position) > ERR_THR){
                    motor.speed(motorPin, -Constants::speedLift);
                    ZiplineLiftBase::positionBackLift = analogRead(Constants::potBack);
                }
            }
        }
    }
}
void ZiplineLiftBase::liftFront(){
    ZiplineLiftBase::moveLift(Constants::frontLift, Constants::voltageUpFront);
}
void ZiplineLiftBase::dropFront(){
    ZiplineLiftBase::moveLift(Constants::frontLift, Constants::voltageDownFront);
}
void ZiplineLiftBase::liftBack(){
    ZiplineLiftBase::moveLift(Constants::backLift, Constants::voltageUpBack);
}
void ZiplineLiftBase::dropBack(){
    ZiplineLiftBase::moveLift(Constants::backLift, Constants::voltageDownBack);
}

 ZiplineLiftBase ziplineLift;
