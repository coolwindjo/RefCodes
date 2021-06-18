#include <limits.h>
#include "6_Replace_Method_with_Method_Object.h"
#include "gtest/gtest.h"

TEST(AccountTC, DeltaTest)
{
	Account acc;
	EXPECT_DOUBLE_EQ(0.1, acc.delta());
	EXPECT_EQ(700, acc.gamma(0,0,0));
}
