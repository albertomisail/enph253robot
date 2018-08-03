#include "gtest/gtest.h"
#include <Movement.h>

class MovementTest : public ::testing::Test {
protected:
	virtual void SetUp() {}
	virtual void TearDown() {}
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
