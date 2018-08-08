#include "Movement.h"
#include "OLED_I2C.h"
Movement::Movement() : leftEnc(Constants::LEFT_ENC_PIN), rightEnc(Constants::RIGHT_ENC_PIN) {}

void Movement::start(MovementInstruction instruction) {
    start(instruction.leftDir, instruction.rightDir, instruction.leftAmt, instruction.rightAmt, instruction.correctionSpeed);
}

void Movement::start(int8_t leftDir_, int8_t rightDir_, int16_t leftAmt_, int16_t rightAmt_, int16_t correctionSpeed_)
{
    previousTime = millis();
    motor.init();
    leftDir = leftDir_;
    rightDir = rightDir_;
    leftAmt = leftAmt_;
    rightAmt = rightAmt_;
    moveState = true;
    Encoder::poll();
    leftInit = leftEnc.getPosition();
    rightInit = rightEnc.getPosition();
    correctionSpeed = correctionSpeed_;
}

void Movement::stop() {
    moveState = false;
}

bool Movement::isMoving() const {
    return moveState;
}

bool Movement::oneSideFinished(int16_t leftPos, int16_t rightPos) {
    if(leftPos >= leftInit+leftAmt && rightPos >= rightInit + rightAmt) {
        motor.speed(Constants::MOTOR_LEFT, 0);
        motor.speed(Constants::MOTOR_RIGHT, 0);
        moveState = false;
        return false;
    }
    if(leftPos >= leftInit+leftAmt) {
        motor.speed(Constants::MOTOR_LEFT, 0);
        motor.speed(Constants::MOTOR_RIGHT, rightDir*(correctionSpeed+10));
    } else {
        motor.speed(Constants::MOTOR_LEFT, leftDir*(correctionSpeed+10));
        motor.speed(Constants::MOTOR_RIGHT, 0);
    }
    return true;
}

int cnt = 0;
bool Movement::poll() {

    cnt++;
    /*if(cnt%2) {
        oled.clrPixel(50, 50);
    } else {
        oled.setPixel(50, 50);
    }
    oled.update();
    delay(50);
    */
    if(!moveState) {
        return false;
    }
    int32_t now = millis();
    deltaT = now - previousTime;
    Encoder::poll();
    //Not too sure what this does
    if(deltaT < Constants::LINE_FOLLOW_POLL_TIME) {
        return true;
    }
    int16_t leftPos = leftEnc.getPosition();
    int16_t rightPos = rightEnc.getPosition();

    //difference between left encoder's position multiplied by how much we want to go to the right + half of left amoun
    int16_t expectedRightPos = ((leftPos-leftInit)*(rightAmt) + leftAmt/2)/leftAmt + rightInit;
    int16_t error = expectedRightPos - rightPos;

    if(leftPos >= leftInit+leftAmt || rightPos >= rightInit+rightAmt)
    {
        /*oled.clrScr();
        oled.printNumI(cnt, 0, 0);
        oled.update();
        delay(1000);*/
        return oneSideFinished(leftPos, rightPos);
    }

    int16_t p = Constants::PROPORTIONAL_MOVEMENT*error;
    if(p > 0) {
        p -= Constants::PROPORTIONAL_MOVEMENT/2;
    }
    else if(p < 0) {
        p += Constants::PROPORTIONAL_MOVEMENT/2;
    }

    if(error == previousError)
    {
        ++counter;
    } else {
        counter = 1;
    }

    int16_t d = Constants::DERIVATIVE_MOVEMENT*(error-previousError) / (deltaT*counter);

    int16_t g = p+d;

    int16_t leftVal = leftDir*max(correctionSpeed, correctionSpeed-g);
    int16_t rightVal = rightDir*max(correctionSpeed, correctionSpeed+g);

    motor.speed(Constants::MOTOR_LEFT, leftVal);
    motor.speed(Constants::MOTOR_RIGHT, rightVal);

    previousError = error;
    previousTime = now;
    return true;
}

void Movement::move(int8_t dirl, int8_t dirr, int16_t leftdist, int16_t rightdist, int16_t speed)
{
    start(dirl, dirr, leftdist, rightdist, speed);
    while(poll()) {}
}

void Movement::move(MovementInstruction instruction) {
    move(instruction.leftDir, instruction.rightDir, instruction.leftAmt, instruction.rightAmt, instruction.correctionSpeed);
}


MovementInstruction Movement::reverseLast()
{
    MovementInstruction ans;
    ans.leftDir = -leftDir;
    ans.rightDir = -rightDir;
    ans.leftAmt = leftEnc.getPosition()-leftInit;
    ans.rightAmt = rightEnc.getPosition()-rightInit;
    ans.correctionSpeed = correctionSpeed;
    return ans;
}
