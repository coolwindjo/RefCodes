#include "sample1.h"
#include "gtest/gtest.h"

TEST(ParameterizeMethod, tenPercentRaise)
{
	EXPECT_EQ(11000, tenPercentRaise(10000));
	EXPECT_EQ(10500, fivePercentRaise(10000));
}
