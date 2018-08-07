#include "gtest/gtest.h"
#include <Movement.h>
#include "TestHelper.h"
#include <PIDSpeed.h>

class PIDSpeedTest : public ::testing::Test {
protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
public:
    //static void checkMovementResponse(int leftEncoderVal, int rightEncoderVal, ) {

    //}
};

TEST_F(PIDSpeedTest, stuckTest) {
    // Make sure that this behaves correctly when it moves too slow
    Encoder enc(PB0);
    enc.reset();
    PIDSpeed speed;
    speed.start(100, 100, enc);
    for(int i=0;i<10;++i) {
    	delay(100);
    	speed.poll();
    }
    ASSERT_GT(speed.getSpeed(), 100);
    ASSERT_LE(speed.getSpeed(), 255);
}

TEST_F(PIDSpeedTest, tooFastTest) {
    Encoder enc(PB0);
    enc.reset();
    PIDSpeed speed;
    speed.start(100, 100, enc);
    for(int i=0;i<100;++i) {
    	if(i%2) {
    		RobotTest::setDigitalValue(PB0, HIGH);
    	} else {
    		RobotTest::setDigitalValue(PB0, LOW);
    	}
        delay(5);
        speed.poll();
    }
    ASSERT_LT(speed.getSpeed(), 100);
    ASSERT_GE(speed.getSpeed(), 0);
}

// TODO: The rest of the movement tests
