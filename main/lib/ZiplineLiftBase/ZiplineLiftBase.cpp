#include "ZiplineLiftBase.h"
#include "OLED_I2C.h"

const uint16_t ERR_THR = 25;


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
        if (ZiplineLiftBase::positionFrontLift <= Constants::voltageUpFront || ZiplineLiftBase::positionFrontLift >= Constants::voltageDownFront) {
            if(positionFrontLift < position){
                //Actual code
                /*
                while(abs(positionFrontLift-position) > ERR_THR) {
                    motor.speed(motorPin, Constants::speedLift);
                    ZiplineLiftBase::positionFrontLift = analogRead(Constants::potFront);
                }
                */
                // For loop for testing and printing pot value to OLED
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
                /*
                while(abs(positionFrontLift-position) > ERR_THR) {
                    motor.speed(motorPin, -Constants::speedLift);
                    ZiplineLiftBase::positionFrontLift = analogRead(Constants::potFront);
                }
                */
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
                /*
                while(abs(positionBackLift-position) > ERR_THR){
                    motor.speed(motorPin, Constants::speedLift);
                    ZiplineLiftBase::positionBackLift = analogRead(Constants::potBack);
                }
                */
                for(int32_t i =0; abs(positionBackLift-position) > ERR_THR; ++i){
                    motor.speed(motorPin, Constants::speedLift);
                    ZiplineLiftBase::positionBackLift = analogRead(Constants::potBack);
                    if (i%100 == 0) {
                        oled.clrScr();
                        oled.printNumI(positionBackLift, 0, 0);
                        oled.update();
                    }
                }
                motor.speed(motorPin,0);
            }else{
                /*
                while(abs(positionBackLift-position) > ERR_THR){
                    motor.speed(motorPin, -Constants::speedLift);
                    ZiplineLiftBase::positionBackLift = analogRead(Constants::potBack);
                }
                */
                for(int32_t i =0; abs(positionBackLift-position) > ERR_THR; ++i){
                    motor.speed(motorPin, -Constants::speedLift);
                    ZiplineLiftBase::positionBackLift = analogRead(Constants::potBack);
                    if (i%100 == 0) {
                        oled.clrScr();
                        oled.printNumI(positionBackLift, 0, 0);
                        oled.update();
                    }
                }
                motor.speed(motorPin,0);
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
