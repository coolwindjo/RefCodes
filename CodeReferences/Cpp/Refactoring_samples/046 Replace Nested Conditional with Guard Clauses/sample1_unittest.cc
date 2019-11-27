#include "sample1.h"
#include "gtest/gtest.h"

TEST(ReplaceNestedConditionalWithGuardClauses, getPayAmount)
{
	EXPECT_EQ(100, getPayAmount(0, 0, 0));
	EXPECT_EQ(1000, getPayAmount(0, 0, 1));
	EXPECT_EQ(50, getPayAmount(0, 1, 0));
	EXPECT_EQ(50, getPayAmount(0, 1, 1));
	EXPECT_EQ(200, getPayAmount(1, 0, 0));
	EXPECT_EQ(200, getPayAmount(1, 0, 1));
	EXPECT_EQ(200, getPayAmount(1, 1, 0));
	EXPECT_EQ(200, getPayAmount(1, 1, 1));
}
