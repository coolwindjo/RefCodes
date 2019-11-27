#include <limits.h>
#include "1_ExtractMethod.h"
#include "gtest/gtest.h"

TEST(CalculateOutstandingTC, RangeTest)
{
	InitOrders();
	EXPECT_LT(0.0, CalculateOutstanding(0.0));
	EXPECT_GT(LONG_MAX, CalculateOutstanding(0.0));
}
