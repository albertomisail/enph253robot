#include "testAll.h"

// void testUltrasound() {
//     oled.clrScr();
//     oled.print(const_cast<char*>("dist: "), 0, 0);
//     //oled.printNumI(ultrasound.measureDistance(0), 35, 0);
//     HCSR04 hcsr;
//     hcsr.init(Constants::trigPins[0], Constants::echoPins[0]);
//     long disc = hcsr.readDisctanceInMm();
//     oled.printNumI(disc, 35, 0);
//     oled.update();
//     delay(200);
// }

// void testEncoder() {
//     Encoder enc(PB13);
//     for(int i=0;;++i) {
//         if(i%100 == 0) {
//             oled.clrScr();
//             oled.printNumI(enc.getPosition(), 0, 0);
//             oled.update();
//         }
//         enc.poll();
//         delay(1);
//     }
// }

// void testClawOnly() {
//     claw.deployBridge();
// }

// void testMenu() {
//     Menu m;
//     m.run();
// }

// void testLineFollow() {
//     Menu m;
//     m.run();
//     lineFollower.start();
//     Encoder enc(PB14);
//     for(int i=0;lineFollower.poll();++i) {
//         enc.poll();
//         if(i%200 == 0)
//         {
//             oled.clrScr();
//             oled.print(const_cast<char*>("L:"), 0, 0);
//             oled.print(const_cast<char*>("R:"), 0, 10);
//             oled.print(const_cast<char*>("E:"), 0, 20);
//             oled.print(const_cast<char*>("G:"), 0, 30);
//             oled.print(const_cast<char*>("ER"), 0, 40);
//             oled.print(const_cast<char*>("EN"), 0, 50);
//             oled.printNumI(lineFollower.sensorLeftReading, 20, 0);
//             oled.printNumI(lineFollower.sensorRightReading, 20, 10);
//             oled.printNumI(lineFollower.sensorEdgeReading, 20, 20);
//             oled.printNumI(lineFollower.g, 20, 30);
//             oled.printNumI(lineFollower.error, 20, 40);
//             oled.printNumI(enc.getPosition(), 20, 50);
//             oled.update();
//         }
//     }
//     // drop bridge
// }

// void testPWM() {
//     oled.clrScr();
//     oled.printNumI(analogRead(PA1), 0, 0);
//     oled.printNumI(analogRead(PA3), 0, 10);
//     oled.update();
// }

// void testFFT() {
//     oled.clrScr();
//     FFTPair fftPair = fft.sample();
//     oled.print(const_cast<char*>("1:"), 0, 0);
//     oled.print(const_cast<char*>("10:"), 0, 10);
//     oled.printNumI(fftPair.lowAmount, 30, 0);
//     oled.printNumI(fftPair.highAmount, 30, 10);
//     oled.printNumI(analogRead(Constants::IR_BEACON_PIN), 30, 20);
//     oled.printNumI(fft.sampleTime, 50, 30);
//     oled.update();
//     delay(50);
// }

// void testEncoders(){


//     Encoder encLeft(PB14);
//     Encoder encRight(PB15);
//     uint8_t OTHER_PIN = PA1;

//     int32_t before = millis();
//     int32_t b, a;
//     for(int32_t i=0;millis() - before < 10000;++i) {
//         b=a;
//         a = micros();
//         Encoder::poll();
//         if(i%10000 == 0) {
//             motor.speed(Constants::MOTOR_LEFT, -Constants::BASE_SPEED.getVal());
//             motor.speed(Constants::MOTOR_RIGHT, Constants::BASE_SPEED.getVal());
//             oled.clrScr();
//             oled.printNumI(encLeft.getPosition(), 0, 0);
//             oled.printNumI(encRight.getPosition(), 0, 10);
//             oled.printNumI(analogRead(OTHER_PIN), 0, 20);
//             oled.printNumI(a-b, 0, 30);
//             oled.update();
//         }
//     }
// }

void testLFandReverse() {

    claw.init();
    Menu m;
    m.run();

    lineFollower.start();
    Encoder leftEnc(Constants::LEFT_ENC_PIN);
    Encoder rightEnc(Constants::RIGHT_ENC_PIN);
    oled.invertText(false);
    for(int32_t i=0;lineFollower.poll();++i) {
        Encoder::poll();
        if(rightEnc.getPosition()>=145){
            break;
        }
        if(i%10000 == 0)
        {
            oled.clrScr();
            oled.print(const_cast<char*>("L:"), 0, 0);
            oled.print(const_cast<char*>("R:"), 0, 10);
            oled.print(const_cast<char*>("E:"), 0, 20);
            oled.print(const_cast<char*>("G:"), 0, 30);
            oled.print(const_cast<char*>("ER"), 0, 40);
            oled.print(const_cast<char*>("EN"), 0, 50);
            oled.printNumI(lineFollower.sensorLeftReading, 20, 0);
            oled.printNumI(lineFollower.sensorRightReading, 20, 10);
            oled.printNumI(lineFollower.sensorEdgeReading, 20, 20);
            oled.printNumI(lineFollower.sensorLeftReadingAmb, 55, 0);
            oled.printNumI(lineFollower.sensorRightReadingAmb, 55, 10);
            oled.printNumI(lineFollower.sensorEdgeReadingAmb, 55, 20);
            oled.printNumI(lineFollower.sensorLeftReadingPow, 90, 0);
            oled.printNumI(lineFollower.sensorRightReadingPow, 90, 10);
            oled.printNumI(lineFollower.sensorEdgeReadingPow, 90, 20);
            oled.printNumI(lineFollower.g, 20, 30);
            oled.printNumI(lineFollower.error, 20, 40);
            oled.printNumI(leftEnc.getPosition(), 20, 50);
            oled.printNumI(rightEnc.getPosition(), 60, 50);
            oled.printNumI(lineFollower.lastCompTime, 90, 30);
            if(i%20000 == 0)
            {
                oled.print(const_cast<char*>("."), 100, 0);
            }
            oled.update();
        }
    }

    int16_t leftEncStore = leftEnc.getPosition();
    int16_t rightEncStore = rightEnc.getPosition();
    motor.speed(0, 0);
    motor.speed(1, 0);

   
    /*
    for(int i = 0; i < 10; i++){
        if(infrared.objectDetected(Constants::distantInfaredThreshold)){
            flag = false;
        }
    } */
    // while(!infrared.objectDetected(Constants::distantInfaredThreshold)) {
    //     cnt = 0;
    //     oled.clrScr();
    //     oled.printNumI(infrared.makeMeasurement(),0,0);
    //     oled.update();
    //     delay(2000);
    //     if (cnt%100 == 0) {

    // //InfraredBase infrared;
    Movement mvt;
    oled.clrScr();
    oled.print(const_cast<char*>("Rotate"),0,0);
    oled.update();
    //Movement mvt;
    //mvt.start(-1, 1, 3, 3, 100);
    //while(mvt.poll()) {}
    oled.clrScr();
    oled.print(const_cast<char*>("After first rotation"),0,0);
    oled.update();
    delay(1000);
    //uint16_t cnt;
    mvt.start(1,-1,12,12,75);
    infrared.startMeasurement();
    for(int i=0;mvt.poll();) {
        if(!infrared.poll()) {
            if(++i%5 == 0) {
                Serial.println(infrared.lastMeasurement());
                // oled.clrScr();
                // oled.printNumI(infrared.lastMeasurement(),0,0);
                // oled.update();
            }
            if(infrared.objectDetected(Constants::distantInfraredThreshold1)) {
                Serial.println("!!!!!!!!!!!!!!!!!");
                // oled.print("!!!!!!!!!!!!", 0, 20);
                // oled.update();
                // delay(1000);
                break;
            }
            infrared.startMeasurement();
        }
    }
    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0);
    /*
    for(int i = 0; i < 10; i++){
        if(infrared.objectDetected(Constants::distantInfaredThreshold)){
            flag = false;
        }
    } */
    // while(!infrared.objectDetected(Constants::distantInfaredThreshold)) {
    //     cnt = 0;
    //     oled.clrScr();
    //     oled.printNumI(infrared.makeMeasurement(),0,0);
    //     oled.update();
    //     delay(2000);
    //     if (cnt%100 == 0) {

    //     }
    //     mvt.start(1,-1,1,1);
    //     while(mvt.poll()){}
    //     cnt++;
    // }

    oled.clrScr();
    oled.print(const_cast<char*>("DETECTED FAR"),0,10);
    oled.update();
    delay(2000);
    mvt.start(1,1,10,10, 105);
    infrared.startMeasurement();
    for(int i = 0; mvt.poll();){
        if(!infrared.poll()) {
            if(i++%5 == 0) {
                Serial.println(infrared.lastMeasurement());
            }
            if(infrared.objectDetected(Constants::pickUpInfraredThreshold1)){
                Serial.println("????????????");
                break;
            }
            infrared.startMeasurement();
        }
    }
    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0);
    oled.print(const_cast<char*>("DETECTED, PICKING UP"),0,10);
    oled.update();
    // delay(1000);
    // ziplineLift.dropFront();
    delay(2000);

    claw.pickEwok();
    oled.clrScr();
    oled.print(const_cast<char*>("Picked up Ewok, looking for line"),0,0);
    oled.update();
    delay(2000);
    mvt.start(1,1,7,5,100);
    while(mvt.poll()){}
    mvt.start(1,-1,800,800,75);
    oled.print("mvt.start",0,0);
    oled.update();
    lineFollower.startQRD();
    for(int32_t i=0;mvt.poll();){
        if(!lineFollower.QRDPoll()) {
            // Serial.println("i=" + i);
            if(i++>0){
                // if(i%1 == 0) {
                //     Serial.println(lineFollower.QRDMeasurement('r'));
                //     Serial.println("bla");
                // }
                if(lineFollower.QRDMeasurement('r')<=Constants::RIGHT_THRESHOLD.getVal()){
                    oled.clrScr();
                    oled.print(const_cast<char*>("see black"),0,0);
                    oled.printNumI(i, 0, 10);
                    oled.update();

                    // Serial.println(lineFollower.QRDMeasurement('r'));
                    // Serial.println("blu");
                    break;
                }
            }
            lineFollower.startQRD();
        }
    }
    motor.speed(0, 0);
    motor.speed(1, 0);
    //Serial.println("!!SAW BLACK");
    delay(2000);

    lineFollower.start();

    while(lineFollower.poll()) {}

    // oled.print(const_cast<char*>("TRY turn"), 0, 0);
    // oled.update();
    // mvt.start(-1, 1, 10, 10);
    // while(mvt.poll()) {}
    // delay(500);
    // oled.print(const_cast<char*>("TRY more turn"), 0, 0);
    // oled.update();
    // mvt.start(-1, -1, 6, 6);
    // while(mvt.poll()) {}
    // delay(500);

    // claw.deployBridge();
    // oled.clrScr();
    // oled.print(const_cast<char*>("BRIDGE DROPPED"), 0, 0);
    // oled.update();

    // oled.clrScr();
    // oled.printNumI(leftEncStore, 0, 0);
    // oled.printNumI(rightEncStore, 0, 10);
    // oled.update();
    // delay(20000);

    //Rotating to find Ewok
    /*
    motor.speed(Constants::MOTOR_LEFT, Constants::CORRECTION_SPEED/2);
    motor.speed(Constants::MOTOR_RIGHT, -Constants::CORRECTION_SPEED/2);
    while (!infrared.objectDetected(Constants::pickUpInfraredThreshold)) {
        oled.clrScr();
        oled.printNumI(infrared.makeMeasurement(),0,0);
        oled.update();
    }
    motor.speed(Constants::MOTOR_LEFT, 0);
    motor.speed(Constants::MOTOR_RIGHT, 0);
    oled.print(const_cast<char*>("EWOK DETECTED"),0,10);
    oled.update();
    claw.pickEwok();
    delay(10000); */
}

void testPickingUpEwok(){
    //oled.clrScr();
    //oled.print(const_cast<char*>("COMMENTED OUT"), 0, 0);
    //oled.update();
    //delay(10000);

    oled.clrScr();
    oled.print(const_cast<char*>("COMMENTED OUT"), 0, 0);
    oled.update();
    delay(10000);
    /*
    oled.clrScr();
    oled.update();
    delay(1000);
    oled.clrScr();
    oled.print(const_cast<char*>("STARTING EWOK TEST"), 0, 0);
    oled.update();

    delay(1000);
    infrared.init();
    claw.init();
    oled.clrScr();
    oled.print(const_cast<char*>("DONE INITS"), 0, 0);
    oled.update();
    delay(1000);
    int i = 0;
    while(true) {
        if(!infrared.poll()) {
            if(i++%5 == 0) {
                Serial.println(infrared.lastMeasurement());
            }
            if(infrared.objectDetected(Constants::pickUpInfraredThreshold)){
                Serial.println("????????????");
                break;
            }
            infrared.startMeasurement();
        }
    }
    oled.print(const_cast<char*>("SAW SOMETHING"), 0, 0);
    oled.update();
    delay(1000);
    claw.pickEwok();
    oled.print(const_cast<char*>("EWOK PICKED"), 0, 0);
    oled.update();
    delay(500);
    */
}

// void testMovement() {
//     oled.clrScr();
//     oled.print(const_cast<char*>("MOVEMENT TEST:"), 0, 0);
//     oled.update();
//     delay(1000);
//     Movement m;
//     m.start(1, -1, 120, 120);
//     while(m.poll()) {}
//     oled.clrScr();
//     oled.print(const_cast<char*>("DONE"), 0, 0);
//     oled.update();
//     delay(5000);
// }

void testLift(){
    while(true) {
        oled.clrScr();
        oled.print(const_cast<char*>("UP"), 0, 0);
        oled.update();
        delay(2000);
        ziplineLift.liftFront();
        delay(2000);
        oled.clrScr();
        oled.print(const_cast<char*>("DOWN"), 0, 0);
        oled.update();
        delay(2000);
        ziplineLift.dropFront();
        delay(2000);
    }
}

// void pickUpFirstEwok() {
//     Menu m;
//     m.run();
//     lineFollower.start();
//     Encoder leftEnc(Constants::LEFT_ENC_PIN);
//     Encoder rightEnc(Constants::RIGHT_ENC_PIN);
//     oled.invertText(false);
//     for(int32_t i=0;lineFollower.poll();++i) {
//         //Encoder::poll();
//         if(leftEnc.getPosition() > 90) {
//             lineFollower.stop();
//         }
//         if(i%10000 == 0)
//         {
//             oled.clrScr();
//             oled.print(const_cast<char*>("L:"), 0, 0);
//             oled.print(const_cast<char*>("R:"), 0, 10);
//             oled.print(const_cast<char*>("E:"), 0, 20);
//             oled.print(const_cast<char*>("G:"), 0, 30);
//             oled.print(const_cast<char*>("ER"), 0, 40);
//             oled.print(const_cast<char*>("EN"), 0, 50);
//             oled.printNumI(lineFollower.sensorLeftReading, 20, 0);
//             oled.printNumI(lineFollower.sensorRightReading, 20, 10);
//             oled.printNumI(lineFollower.sensorEdgeReading, 20, 20);
//             oled.printNumI(lineFollower.sensorLeftReadingAmb, 55, 0);
//             oled.printNumI(lineFollower.sensorRightReadingAmb, 55, 10);
//             oled.printNumI(lineFollower.sensorEdgeReadingAmb, 55, 20);
//             oled.printNumI(lineFollower.sensorLeftReadingPow, 90, 0);
//             oled.printNumI(lineFollower.sensorRightReadingPow, 90, 10);
//             oled.printNumI(lineFollower.sensorEdgeReadingPow, 90, 20);
//             oled.printNumI(lineFollower.g, 20, 30);
//             oled.printNumI(lineFollower.error, 20, 40);
//             oled.printNumI(leftEnc.getPosition(), 20, 50);
//             oled.printNumI(rightEnc.getPosition(), 60, 50);
//             oled.printNumI(lineFollower.lastCompTime, 90, 30);
//             if(i%20000 == 0)
//             {
//                 oled.print(const_cast<char*>("."), 100, 0);
//             }
//             oled.update();
//         }
//     }

//     int16_t encoderReading = leftEnc.getPosition();

//     Movement move;
//     move.start(-1,1,6,6);
//     while(move.poll()) {};

//     InfraredBase infrared;
//     //TODO: what to do if ewok not detected?
//     bool ewokDetected = false;

//     //Really bad way of doing this but this is just limiting the movement so we don't overrotate
//     for(int i = 0; i < 20 ; i++) {
//         move.start(1,-1,1,1);
//         while(move.poll()) {}
//         if (infrared.objectDetected(Constants::distantInfaredThreshold)) {
//             ewokDetected = true;
//             break;
//         }
//     }

//     if (ewokDetected) {
//         while(infrared.makeMeasurement()<=(Constants::pickUpInfraredThreshold)){
//             move.start(1,1,1,1);
//             while(move.poll()) {}
//         }
//         claw.pickEwok();
//     }

//     lineFollower.init(-4);
//     lineFollower.start();
//     while(lineFollower.poll()){}
// }

// void crossBridge() {
//     // Assumes that we are at the beginning of the bridge, lined up straight to it,
//     // and we're about to cross the bridge.  This will bring us toward the 2nd ewok.
//     Menu m;
//     m.run();
//     Movement move;
//     move.start(1, 1, 48, 40);
//     while(move.poll()) {}
//     delay(1000);
//     move.start(1, -1, 6, 6);
//     while(move.poll()) {}
//     delay(1000);
//     move.start(1, 1, 24, 24);
//     while(move.poll()) {}
//     delay(1000);

//     bool ewokDetected = false;

//     for(int i = 0; i < 20 ; i++) {
//         move.start(-1,1,1,1);
//         while(move.poll()) {}
//         if (infrared.objectDetected(Constants::distantInfaredThreshold)) {
//             ewokDetected = true;
//             break;
//         }
//     }

//     if (ewokDetected) {
//         while(infrared.makeMeasurement()<=(Constants::pickUpInfraredThreshold)){
//             move.start(1,1,1,1);
//             while(move.poll()) {}
//         }
//         claw.pickEwok();
//     }
// }

// void findFFTSignal() {

// }

void testInfrared() {
    infrared.startMeasurement();
    while(true) {
        if(!infrared.poll()) {
            Serial.println(infrared.lastMeasurement());
            infrared.startMeasurement();
        }
    }
}

void encoderReadings() {
    Encoder leftEnc(Constants::LEFT_ENC_PIN);
    Encoder rightEnc(Constants::RIGHT_ENC_PIN);
    int a = 0;
    while(true) {
        Encoder::poll();
        if(millis()%50 == 0 && a == 0) {
            Serial.print(leftEnc.getPosition());
            Serial.print(const_cast<char*>(" "));
            Serial.print(rightEnc.getPosition());
            Serial.println();
            ++a;
        } else {
            a = 0;
        }
    }
}

void fftTuning() {
    const int8_t MULTIPLEX_PIN = PA8;
    pinMode(MULTIPLEX_PIN, OUTPUT);
    digitalWrite(MULTIPLEX_PIN, LOW);
    delay(20);
    while(true) {
        float f10=0, f1=0;
        for(int i=0;i<10;++i) {
            FFTPair fftPair = fft.sample();
            f10 += fftPair.highAmount;
            f1 += fftPair.lowAmount;
        }
        float totalAmount = sqrt(f10*f10 + f1*f1);
        Serial.print(totalAmount);
        Serial.print("\t");
        Serial.print(f1);
        Serial.print("\t");
        Serial.print(f10);
        Serial.println();
        delay(100);
    }
}
