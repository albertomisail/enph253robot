#include "gtest/gtest.h"
#include <Movement.h>
#include "TestHelper.h"
#include <Constants.h>

class MovementTest : public ::testing::Test {
protected:
	virtual void SetUp() {}
	virtual void TearDown() {}
public:
	//static void checkMovementResponse(int leftEncoderVal, int rightEncoderVal, ) {

	//}
};

TEST_F(MovementTest,isMoving) {
	Movement m;
	m.start(1, 1, 100, 100, 100);
	ASSERT_TRUE(m.isMoving());
	m.start(1, 1, 100, 100, 100);
	ASSERT_TRUE(m.isMoving());
	m.stop();
	ASSERT_FALSE(m.isMoving());
	m.stop();
	ASSERT_FALSE(m.isMoving());
}

TEST_F(MovementTest,history) {
	Movement m;
	m.start(-1, -1, 100, 100, 100);
	RobotTest::mockEncoderSteps(Constants::LEFT_ENC_PIN, 10, millis());
	RobotTest::mockEncoderSteps(Constants::RIGHT_ENC_PIN, 10, millis());
	ASSERT_GT(millis(), 0);
	ASSERT_TRUE(m.poll());
	MovementInstruction inst = m.reverseLast();
	ASSERT_EQ(1, inst.leftDir);
	ASSERT_EQ(1, inst.rightDir);
	ASSERT_EQ(10, inst.leftAmt);
	ASSERT_EQ(10, inst.rightAmt);
	ASSERT_EQ(100, inst.correctionSpeed);
}

// TODO: The rest of the movement tests
