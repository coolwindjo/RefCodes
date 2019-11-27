#include "sample1.h"
#include "gtest/gtest.h"

TEST(A, B)
{
	Account account;
	account.Init();
	EXPECT_EQ(300, account.GetFlowBetween(time(0) - 2 * Account::OneDay(), time(0)));
}