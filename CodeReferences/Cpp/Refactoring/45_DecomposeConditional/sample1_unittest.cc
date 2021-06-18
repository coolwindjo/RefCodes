#include "sample1.h"
#include "gtest/gtest.h"

TEST(DecomposeConditional, heatingCharge)
{
	EXPECT_EQ(85000, heatingCharge(5, 50000));
	EXPECT_EQ(60000, heatingCharge(6, 60000));
	EXPECT_EQ(70000, heatingCharge(10, 70000));
	EXPECT_EQ(130000,heatingCharge(11, 80000));
}
