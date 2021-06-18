#include "sample1.h"
#include "gtest/gtest.h"

TEST(ConsolidateDuplicateConditionalFragments , getTotal)
{
	EXPECT_EQ(9800, getTotal(0));
	EXPECT_EQ(9500, getTotal(1));
}
