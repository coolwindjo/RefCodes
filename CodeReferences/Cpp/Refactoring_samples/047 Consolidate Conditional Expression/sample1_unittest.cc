#include "sample1.h"
#include "gtest/gtest.h"

TEST(ConsolidateConditionalExpression, disabilityAmount)
{
	EXPECT_EQ(0, disabilityAmount(1, 12, 0));
	EXPECT_EQ(0, disabilityAmount(1, 12, 1));
	EXPECT_EQ(0, disabilityAmount(1, 13, 0));
	EXPECT_EQ(0, disabilityAmount(1, 13, 1));
	EXPECT_EQ(10000, disabilityAmount(2, 12, 0));
	EXPECT_EQ(0, disabilityAmount(2, 12, 1));
	EXPECT_EQ(0, disabilityAmount(2, 13, 0));
	EXPECT_EQ(0, disabilityAmount(2, 13, 1));
}
