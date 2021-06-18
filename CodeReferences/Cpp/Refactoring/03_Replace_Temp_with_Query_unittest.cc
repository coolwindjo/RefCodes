#include <limits.h>
#include "3_Replace_Temp_with_Query.h"
#include "gtest/gtest.h"

TEST(GetPriceTC, OutputValTest)
{
	EXPECT_DOUBLE_EQ(142500, getPrice());
}
