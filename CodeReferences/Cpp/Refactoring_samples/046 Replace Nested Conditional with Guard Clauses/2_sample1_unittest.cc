#include "sample1.h"
#include "gtest/gtest.h"

TEST(ReplaceNestedConditionalWithGuardClauses, getPayAmount)
{
	EXPECT_LT(getAdjustedCapital(50.0, 50.0, 12.0) - 208.333, 0.0001);
}
