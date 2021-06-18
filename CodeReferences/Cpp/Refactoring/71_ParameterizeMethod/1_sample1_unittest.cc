#include "sample1.h"
#include "gtest/gtest.h"

TEST(ParameterizeMethod, tenPercentRaise)
{
	EXPECT_EQ(11000, tenPercentRaise(10000));
	EXPECT_EQ(10500, fivePercentRaise(10000));
}

TEST(ParameterizeMethod, raise)
{
	EXPECT_EQ(11000, raise(10000, 0.1));
	EXPECT_EQ(10500, raise(10000, 0.05));
}
