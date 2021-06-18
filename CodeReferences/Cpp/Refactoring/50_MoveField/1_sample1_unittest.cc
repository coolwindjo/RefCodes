#include "sample1.h"
#include "gtest/gtest.h"

TEST(MoveField, InterestForAmount_Days)
{
	Account account;
	account.type_.SetInterestRate(0.5);
	EXPECT_LT(abs(1232.88 - account.InterestForAmount_Days(3000, 300)), 0.001);
}
