#include "sample1.h"
#include "gtest/gtest.h"

TEST(SplitTemporaryVariable, GetDistanceTravelled)
{
	EXPECT_GT(0.01, abs(40.3 - GetDistanceTravelled(5)));
}
