#include "LineFollower.h"

void LineFollower::init(int previousError_)
{
    motor.init();
    pinMode(Constants::QRD_POWER_PIN, OUTPUT);
    digitalWrite(Constants::QRD_POWER_PIN, LOW);
    pinMode(Constants::LEFT_QRD_PIN, INPUT);
    pinMode(Constants::RIGHT_QRD_PIN, INPUT);
    pinMode(Constants::EDGE_QRD_PIN, INPUT);
    this->previousError = previousError_;
}

void LineFollower::start() {
    start(4096,4096,Constants::EDGE_THRESHOLD.getVal());
}
void LineFollower::start(int leftStopThreshold_, int rightStopThreshold_, int edgeStopThreshold_) {
    lastTime = 0;
    previousError = 0;
    deltaT = 0, previousTime = 0;
    consec = 0;
    counter = 0;
    lastG = 0;
    state = 0;
    movingState = true;
    leftStopThreshold = leftStopThreshold_;
    rightStopThreshold = rightStopThreshold_;
    edgeStopThreshold = edgeStopThreshold_;
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

    if(sensorLeftReading < leftStopThreshold
    && sensorRightReading < rightStopThreshold
    && sensorEdgeReading < edgeStopThreshold) {
        if(++consec > 1) {
            motor.speed(Constants::MOTOR_LEFT, -255);
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

void LineFollower::startQRD() {
    hasQRDStarted = false;
    isQRDReading = true;
}
void LineFollower::QRDGetInitialReading() {
    sensorLeftReadingAmb = analogRead(Constants::LEFT_QRD_PIN);
    sensorRightReadingAmb = analogRead(Constants::RIGHT_QRD_PIN);
    sensorEdgeReadingAmb = analogRead(Constants::EDGE_QRD_PIN);
    digitalWrite(Constants::QRD_POWER_PIN, HIGH);
    //Serial.println("QRDGetInitialReading()");
    hasQRDStarted = true;
    nextAvailableQRDTime = millis()+2;
}
bool LineFollower::QRDPoll() {
    // Serial.print("hasQRDStarted = ");
    // Serial.print(hasQRDStarted);
    // Serial.print(", ");
    // Serial.print(isQRDReading);
    // Serial.print(", times comparision ");
    // Serial.print(nextAvailableQRDTime);
    // Serial.print(" vs ");
    // Serial.print(millis());
    // Serial.println();
    if(!isQRDReading) return false;
    if(nextAvailableQRDTime > millis()) return true;
    if(!hasQRDStarted) {
        QRDGetInitialReading();
        return true;
    }
    sensorLeftReadingPow = analogRead(Constants::LEFT_QRD_PIN);
    sensorRightReadingPow = analogRead(Constants::RIGHT_QRD_PIN);
    sensorEdgeReadingPow = analogRead(Constants::EDGE_QRD_PIN);
    digitalWrite(Constants::QRD_POWER_PIN, LOW);

    sensorLeftReading = (sensorLeftReadingAmb-sensorLeftReadingPow);
    sensorRightReading = (sensorRightReadingAmb-sensorRightReadingPow);
    sensorEdgeReading = (sensorEdgeReadingAmb-sensorEdgeReadingPow);

    nextAvailableQRDTime = millis()+2;
    isQRDReading = false;
    return false;
}
int16_t LineFollower::QRDMeasurement(char c) const {
    switch(c) {
        case 'l': return sensorLeftReading;
        case 'r': return sensorRightReading;
        case 'e': return sensorEdgeReading;
    }
    return -1;
}
bool LineFollower::QRDIsReading() const {
    return isQRDReading;
}

void LineFollower::findLine(const int8_t& dir) {
    // TODO: blocking findLine method, to
}

LineFollower lineFollower;
