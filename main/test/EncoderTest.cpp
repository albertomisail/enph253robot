#include "gtest/gtest.h"
#include <Encoder.h>
#include "TestHelper.h"

class EncoderTest : public ::testing::Test {
protected:
	virtual void SetUp() {}
	virtual void TearDown() {}
public:
	//static void checkMovementResponse(int leftEncoderVal, int rightEncoderVal, ) {
		
	//}
};

TEST_F(EncoderTest,verifyMockingSteps) {
	pinMode(PB0, INPUT);
	Encoder enc(PB0);
	enc.reset();
	ASSERT_EQ(0, enc.getPosition());
	RobotTest::mockEncoderSteps(PB0, 10, 0);
	ASSERT_EQ(10, enc.getPosition());
}

TEST_F(EncoderTest,reset) {
	pinMode(PB0, INPUT);
	Encoder enc(PB0);
	enc.reset();
	ASSERT_EQ(0, enc.getPosition());
	RobotTest::mockEncoderSteps(PB0, 10, 0);
	ASSERT_EQ(10, enc.getPosition());
	enc.reset();
}

TEST_F(EncoderTest,singletonness) {
	pinMode(PB0, INPUT);
	Encoder enc(PB0);
	enc.reset();
	ASSERT_EQ(0, enc.getPosition());
	RobotTest::mockEncoderSteps(PB0, 10, 0);
	ASSERT_EQ(10, enc.getPosition());
	Encoder enc_copy(PB0);
	ASSERT_EQ(10, enc_copy.getPosition());
	enc_copy.reset();
	ASSERT_EQ(0, enc.getPosition());
	ASSERT_EQ(0, enc_copy.getPosition());
}

TEST_F(EncoderTest,destructor) {
	pinMode(PB0, INPUT);
	pinMode(PB1, INPUT);
	pinMode(PB2, INPUT);
	pinMode(PB3, INPUT);
	pinMode(PB4, INPUT);
	Encoder enc0(PB0);
	Encoder enc1(PB1);
	Encoder enc2(PB2);
	Encoder enc3(PB3);
	enc0.~Encoder();
	enc1.~Encoder();
	enc2.~Encoder();
	enc3.~Encoder();
	Encoder enc4(PB4);
	enc4.reset();
	ASSERT_EQ(0, enc4.getPosition());
	RobotTest::mockEncoderSteps(PB4, 10, 0);
	ASSERT_EQ(10, enc4.getPosition());
}

// TODO: the rest of the encoder tests!
