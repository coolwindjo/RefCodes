#include "sample1.h"
#include "gtest/gtest.h"

TEST(ExtractMethod, GetOutstanding)
{
	InitOrders();
	EXPECT_EQ(10, GetOutstanding());
}
