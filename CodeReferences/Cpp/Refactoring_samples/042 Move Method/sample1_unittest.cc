#include "sample1.h"
#include <cmath>
#include "gtest/gtest.h"

using namespace std;

TEST(MoveMethod, BankCharge)
{
	Account account;

	account.days_overdrawn = 0;
	EXPECT_LT(fabs(account.BankCharge() - 4.5), 0.01);

	account.days_overdrawn = 0.1;
	EXPECT_LT(fabs(account.BankCharge() - 4.5), 0.01);

	account.days_overdrawn = 7;
	EXPECT_LT(fabs(account.BankCharge() - 14.5), 0.01);

	account.days_overdrawn = 7.1;
	EXPECT_LT(fabs(account.BankCharge() - 14.5), 0.01);
}
