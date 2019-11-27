#include <limits.h>
#include "2_Split_Temporary_Variable.h"
#include "gtest/gtest.h"

TEST(GetDistanceTravelledTC, OutputValTest)
{
	EXPECT_DOUBLE_EQ(6.0, GetDistanceTravelled(2));
	EXPECT_DOUBLE_EQ(13.5, GetDistanceTravelled(3));
	EXPECT_DOUBLE_EQ(24.7, GetDistanceTravelled(4));
	EXPECT_DOUBLE_EQ(40.3, GetDistanceTravelled(5));
}
