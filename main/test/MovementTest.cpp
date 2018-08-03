#include "gtest/gtest.h"
#include <Movement.h>
#include "TestHelper.h"

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


// TODO: The rest of the movement tests
