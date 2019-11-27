#include "4_Separate_Query_from_Modifier.h"
#include "gtest/gtest.h"

TEST(SeparateQueryFromModifier, foundMiscreant)
{
	char* people[] = {"Kim", "Lee", "John"};
	EXPECT_EQ(4, checkSecurity(people, 3));
	EXPECT_EQ(1, checkAlert());
}
