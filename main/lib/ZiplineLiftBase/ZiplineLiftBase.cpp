#include "ZiplineLiftBase.h"
#include "OLED_I2C.h"

const uint16_t ERR_THR = 20;


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
        ZiplineLiftBase::positionFrontLift = analogRead(Constants::potFront);
        oled.clrScr();
        oled.printNumI(ZiplineLiftBase::positionFrontLift, 0, 0);
        oled.update();
        delay(2000);
        if (ZiplineLiftBase::positionFrontLift >= Constants::voltageUpFront - ERR_THR && ZiplineLiftBase::positionFrontLift <= Constants::voltageDownFront + ERR_THR) {
            if(positionFrontLift < position){
                //Move down
                int count = 0;
                while(abs(positionFrontLift - position) > ERR_THR){
                    motor.speed(motorPin, Constants::speedLiftDown);
                    int a = abs(positionFrontLift-position);
                    ZiplineLiftBase::positionFrontLift = analogRead(Constants::potFront);
                    if (count%1 == 0) {
                        oled.clrScr();
                        oled.printNumI(positionFrontLift, 0, 20);
                        oled.print(const_cast<char*>("DROPING"), 0, 10);
                        oled.printNumI(a, 0, 30);
                        oled.update();
                    }
                    count++;
                }
                motor.speed(motorPin, 0);
            }else{
                //Move up
                int count = 0;
                while(abs(positionFrontLift - position) > ERR_THR){
                    motor.speed(motorPin, -Constants::speedLiftUp);
                    int a = abs(positionFrontLift-position);
                    ZiplineLiftBase::positionFrontLift = analogRead(Constants::potFront);
                    if (count%1 == 0) {
                        oled.printNumI(positionFrontLift, 0, 20);
                        oled.print(const_cast<char*>("LIFTING"), 0, 10);
                        oled.printNumI(a, 0, 30);
                        oled.update();
                    }
                    count++;
                }
                motor.speed(motorPin, 0);
            }
        }
    }else{
        if (ZiplineLiftBase::positionBackLift <= Constants::voltageUpBack + ERR_THR && ZiplineLiftBase::positionBackLift >= Constants::voltageDownBack - ERR_THR) {
            if(positionBackLift < position){
                /*
                while(abs(positionBackLift-position) > ERR_THR){
                    motor.speed(motorPin, Constants::speedLift);
                    ZiplineLiftBase::positionBackLift = analogRead(Constants::potBack);
                }
                */
                for(int32_t i =0; abs(positionBackLift-position) > ERR_THR; ++i){
                    motor.speed(motorPin, Constants::speedLiftDown);
                    ZiplineLiftBase::positionBackLift = analogRead(Constants::potBack);
                    // if (i%100 == 0) {
                    //     oled.clrScr();
                    //     oled.printNumI(positionBackLift, 0, 0);
                    //     oled.update();
                    // }
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
                    motor.speed(motorPin, -Constants::speedLiftUp);
                    ZiplineLiftBase::positionBackLift = analogRead(Constants::potBack);
                    // if (i%100 == 0) {
                    //     oled.clrScr();
                    //     oled.printNumI(positionBackLift, 0, 0);
                    //     oled.update();
                    // }
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
