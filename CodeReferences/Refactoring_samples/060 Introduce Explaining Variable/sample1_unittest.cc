#include "sample1.h"
#include "gtest/gtest.h"

TEST(IntroduceExplainingVariable, price)
{
	EXPECT_LT(fabs(price(500, 2) - 1100), 0.000001);
	EXPECT_LT(fabs(price(500, 1) - 550), 0.000001);
	EXPECT_LT(fabs(price(550, 2) - 1195), 0.000001);
	EXPECT_LT(fabs(price(550, 1) - 602.5), 0.000001);
}
