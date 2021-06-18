#include "sample1.h"
#include "gtest/gtest.h"

TEST(PreserveWholeObject, WithinRange)
{
	HeatingPlan plan;
	plan.range.low = 14;
	plan.range.high = 20;

	Room room;
	room.range.low = 13;
	room.range.high = 19;
	EXPECT_FALSE(room.WithinPlan(plan));

	room.range.low = 13;
	room.range.high = 20;
	EXPECT_FALSE(room.WithinPlan(plan));

	room.range.low = 13;
	room.range.high = 21;
	EXPECT_FALSE(room.WithinPlan(plan));

	room.range.low = 14;
	room.range.high = 19;
	EXPECT_TRUE(room.WithinPlan(plan));

	room.range.low = 14;
	room.range.high = 20;
	EXPECT_TRUE(room.WithinPlan(plan));

	room.range.low = 14;
	room.range.high = 21;
	EXPECT_FALSE(room.WithinPlan(plan));

	room.range.low = 15;
	room.range.high = 19;
	EXPECT_TRUE(room.WithinPlan(plan));

	room.range.low = 15;
	room.range.high = 20;
	EXPECT_TRUE(room.WithinPlan(plan));

	room.range.low = 15;
	room.range.high = 21;
	EXPECT_FALSE(room.WithinPlan(plan));
}
