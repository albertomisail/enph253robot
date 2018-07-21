#include "LineFollower.h"

void LineFollower::init()
{
    motor.init();
    pinMode(Constants::QRD_POWER_PIN, OUTPUT);
    digitalWrite(Constants::QRD_POWER_PIN, LOW);
    pinMode(Constants::LEFT_QRD_PIN, INPUT);
    pinMode(Constants::RIGHT_QRD_PIN, INPUT);
    pinMode(Constants::EDGE_QRD_PIN, INPUT);
}

void LineFollower::start() {
    movingState = true;
}
void LineFollower::stop() {
    movingState = false;
}

bool LineFollower::isMoving() const {
    return movingState;
}

bool LineFollower::poll()
{
    if(movingState == false) {
        digitalWrite(Constants::QRD_POWER_PIN, LOW);
        return false;
    }
    int32_t now = millis();
    if(state == 0) {
        if(now-previousTime < Constants::LINE_FOLLOW_POLL_TIME) return movingState;
        sensorLeftReadingAmb = analogRead(Constants::LEFT_QRD_PIN);
        sensorRightReadingAmb = analogRead(Constants::RIGHT_QRD_PIN);
        sensorEdgeReadingAmb = analogRead(Constants::EDGE_QRD_PIN);

        digitalWrite(Constants::QRD_POWER_PIN, HIGH);
        state = 1;
        previousTime = millis();
        return movingState;
    }


    deltaT = now - previousTime;

    if(deltaT < 2) return true;

    sensorLeftReadingPow = analogRead(Constants::LEFT_QRD_PIN);
    sensorRightReadingPow = analogRead(Constants::RIGHT_QRD_PIN);
    sensorEdgeReadingPow = analogRead(Constants::EDGE_QRD_PIN);
    digitalWrite(Constants::QRD_POWER_PIN, LOW);

    sensorLeftReading = (sensorLeftReadingAmb-sensorLeftReadingPow);
    sensorRightReading = (sensorRightReadingAmb-sensorRightReadingPow);
    sensorEdgeReading = (sensorEdgeReadingAmb-sensorEdgeReadingPow);

    //sensorLeftReading -= analogRead(Constants::LEFT_QRD_PIN);
    //sensorRightReading -= analogRead(Constants::RIGHT_QRD_PIN);
    //sensorEdgeReading -= analogRead(Constants::EDGE_QRD_PIN);

    //digitalWrite(Constants::QRD_POWER_PIN, LOW);

    if(sensorEdgeReading < Constants::EDGE_THRESHOLD.getVal()) {
        if(++consec > 1) {
            motor.speed(Constants::MOTOR_LEFT, 255);
            motor.speed(Constants::MOTOR_RIGHT, -255);
            delay(40);
            motor.speed(Constants::MOTOR_LEFT, 0);
            motor.speed(Constants::MOTOR_RIGHT, 0);
            movingState = false;
            return false;
        }
    } else {
        consec = 0;
    }

    if(sensorLeftReading < Constants::LEFT_THRESHOLD.getVal()
    && sensorRightReading < Constants:: RIGHT_THRESHOLD.getVal())
    {
        error = 0;
    }
    else if(sensorLeftReading < Constants::LEFT_THRESHOLD.getVal()
         && sensorRightReading >= Constants::RIGHT_THRESHOLD.getVal())
    {
        error = 1;
    }
    else if(sensorLeftReading >= Constants::LEFT_THRESHOLD.getVal()
         && sensorRightReading < Constants::RIGHT_THRESHOLD.getVal())
    {
        error = -1;
    }
    else
    {
        error = max(min(previousError*4, 4), -4);
    }

    int32_t p = (int32_t)Constants::PROPORTIONAL.getVal()*error;
    int32_t i = (int32_t)Constants::INTEGRAL.getVal()*error*now+i;
    i = min(max(i, -((1L)<<12)), (1L)<<12);

    if(error == previousError) {
        ++counter;
    } else {
        counter = 1;
    }
    int32_t d = (int32_t)Constants::DERIVATIVE.getVal() * (error-previousError) / (deltaT*counter);

    g = p+i+d;

    motor.speed(Constants::MOTOR_LEFT, Constants::BASE_SPEED.getVal()-g);
    motor.speed(Constants::MOTOR_RIGHT, Constants::BASE_SPEED.getVal()+g);

    previousError = error;
    previousTime = now;

    state = 0;
    lastCompTime = millis()-now;
    return true;
}

LineFollower lineFollower;
