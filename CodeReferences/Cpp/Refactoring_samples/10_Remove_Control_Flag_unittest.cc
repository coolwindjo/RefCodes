#include "10_Remove_Control_Flag.h"
#include "gtest/gtest.h"

TEST(SeparateQueryFromModifier, foundMiscreant)
{
	char* people[] = {"Kim", "Lee", "John"};
	EXPECT_EQ(4, checkSecurity(people, 3));
	EXPECT_EQ(1, checkAlert());
}
