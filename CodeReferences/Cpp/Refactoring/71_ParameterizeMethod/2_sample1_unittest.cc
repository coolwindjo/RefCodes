#include "sample1.h"
#include "gtest/gtest.h"

TEST(ParameterizeMethod, baseCharge)
{
	EXPECT_EQ(5.5, baseCharge());
}
