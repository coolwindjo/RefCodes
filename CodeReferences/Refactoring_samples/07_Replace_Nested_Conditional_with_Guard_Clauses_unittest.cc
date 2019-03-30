#include "7_Replace_Nested_Conditional_with_Guard_Clauses.h"
#include "gtest/gtest.h"

TEST(GetPayAmountTC, ResultTest)
{
	EXPECT_DOUBLE_EQ(200, getPayAmount(1, 1, 1));
	EXPECT_DOUBLE_EQ(2.5, getAdjustedCapital(deadAmount(), separatedAmount(), retiredAmount()));
}
